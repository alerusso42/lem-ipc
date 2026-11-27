/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matchmaking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 16:05:59 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/27 14:52:35 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/backend.h"

static void	_matchmaking_init(t_B *back, t_matchmaking *matchmaking);
static void	_add_player(t_B *back, t_matchmaking *matchmaking, int id, t_info *info);
static int	_check_match_conditions(t_B *back, t_matchmaking *matchmaking);
static void	_sort_teams(t_B *back, t_matchmaking *matchmaking);
static int	_find_littlest_team(t_B *back, t_matchmaking *matchmaking);
static void	_event_client_new(t_B *back, t_matchmaking *matchmaking, t_msg *msg);
static void	_event_client_del(t_B *back, t_matchmaking *matchmaking, t_msg *msg);
static void	_event_client_quit(t_B *back, t_matchmaking *matchmaking, t_msg *msg);
static void	_event_client_start(t_B *back, t_matchmaking *matchmaking, t_msg *msg);
static void	_event_client_ask_id(t_B *back, t_matchmaking *matchmaking, t_msg *msg);
static void	_event_none(t_B *back, t_matchmaking *matchmaking, t_msg *msg);

#define EVENTS_HANDLER \
(void (*[])(t_B*, t_matchmaking*, t_msg*))\
{\
	[MSGE_INVALID] = _event_none,\
	[MSGE_CLIENT_NEW] = _event_client_new,\
	[MSGE_CLIENT_DEL] = _event_client_del,\
	[MSGE_QUIT] = _event_client_quit,\
	[MSGE_START] = _event_client_start,\
	[MSGE_ID_ASK] = _event_client_ask_id,\
	[MSGE_ID_RECEIVE] = _event_none,\
	[MSGE_NUM] = _event_none\
}

/**
 * @brief A queue poll for both master and clients. On success, game starts.
 * 
 * the msg queue handlers behaves differently for master and clients.
 * ```md
 * | MSG event    | Master                                 | Client
 * | -------------| -------------------------------------- | ------
 * | CLIENT_NEW   | Add client to players list             | -
 * | CLIENT_DEL   | Remove client to players list, free ID | -
 * | CLIENT_QUIT  | exits                                  | exits
 * | START        | If requirements are ok, starts game    | starts game
 * | ID_ASK       | Gives an ID to new client              | -
 * ```
 * 
 * For AI, the first time the conditions are fulfilled triggers the game;
 * for players, the frontend must send a request, that must be accepted. 
 * @param back 
 */
void	B_matchmaking(t_B *back)
{
	t_msg			*msg;
	t_matchmaking	matchmaking;

	debug_log_char(back->proc, "%s matchmaking", back->proc->info.is_master ? "start" : "join");
	_matchmaking_init(back, &matchmaking);
	while (global_sigint == false && back->power_on == true && !matchmaking.start && !back->timeout_matchmaking)
	{
		msg_receive(back->proc);
		while (back->proc->msg_list)
		{
			msg = back->proc->msg_list->content;
			if (msg && *(msg->buff) > MSGE_INVALID && *(msg->buff) < MSGE_NUM)
				EVENTS_HANDLER[(int)*(msg->buff)](back, &matchmaking, msg);
			lst_delone(&back->proc->msg_list, free);
		}
		usleep(WAIT_MATCHMAKING);
		timer_checkAll(back->timers, TIMB_NUM);
	}
	if (!matchmaking.start)
		return (B_stop(back), exit(0));
	if (back->proc->info.is_master)
	{
		back->proc->shared->match.is_start = true;
		debug_log(back->proc, "matchmaking done.");
	}
	return ;
}

//t_matchmaking struct constructor
static void	_matchmaking_init(t_B *back, t_matchmaking *matchmaking)
{
	*matchmaking = (t_matchmaking){0};
	matchmaking->size = 1;
	if (back->proc->info.is_master == true)
		_add_player(back, matchmaking, back->proc->id, &back->proc->info);
	back->players_start_info = matchmaking->players;
	debug_log_int(back->proc, "Matchmaking timeout set in %d milliseconds", back->timers[TIMB_MATCHMAKING].start / 1e3);
	timer_reset(&back->timers[TIMB_MATCHMAKING]);
	timer_reset(&back->timers[TIMB_TEST]);
}

//adds a player to player list.
//if player team is not locked, the player is given the least full team
static void	_add_player(t_B *back, t_matchmaking *matchmaking, int id, t_info *info)
{
	t_list	*node;

	node = lst_new(ft_calloc(1, sizeof(t_player)));
	if (!node)
	{
		lst_clear(&matchmaking->players, free);
		B_error(back, "cannot create node for matchmaking");
	}
	lst_back(&matchmaking->players, node);
	((t_player *)node->content)->id = id;
	if (info->is_team_lock == false)
		info->team = _find_littlest_team(back, matchmaking);
	((t_player *)node->content)->info = *info;
	matchmaking->teams_size[info->team] += 1;
	if (back->proc->info.is_ai == true)
		matchmaking->start = _check_match_conditions(back, matchmaking);
}

//Checks, in order: 
//```md
//	1. Players size is >= low limit
//	2. Player teams are equal in number. If not, sort teams and try again.
//```
static int	_check_match_conditions(t_B *back, t_matchmaking *matchmaking)
{
	bool	try_shuffle;

	try_shuffle = false;
	if (matchmaking->size < back->proc->min_players)
		return (false);
	for (int i = 1; i != back->proc->info.num_team; i++)
		if (matchmaking->teams_size[0] != matchmaking->teams_size[i])
			try_shuffle = true;
	if (try_shuffle == false)
		return (true);
	_sort_teams(back, matchmaking);
	for (int i = 1; i != back->proc->info.num_team; i++)
		if (matchmaking->teams_size[0] != matchmaking->teams_size[i])
			return (false);
	return (true);
}

//Transfer players to the least populated team
static void	_sort_teams(t_B *back, t_matchmaking *matchmaking)
{
	int			team;
	t_list		*node;
	t_player	*player;

	team = _find_littlest_team(back, matchmaking);
	node = matchmaking->players;
	while (node)
	{
		player = node->content;
		if (player && player->info.is_team_lock == false && player->info.team != team)
		{
			matchmaking->teams_size[player->info.team] -= 1;
			matchmaking->teams_size[team] += 1;
			player->info.team = team;
			team = _find_littlest_team(back, matchmaking);
		}
		node = node->next;
	}
}

//Returns the id of the least populated team
static int	_find_littlest_team(t_B *back, t_matchmaking *matchmaking)
{
	int	littlest;

	littlest = 0;
	for (int i = 0; i != back->proc->info.num_team; i++)
	{
		if (matchmaking->teams_size[littlest] > matchmaking->teams_size[i])
			littlest = i;
	}
	return (littlest);
}

//[MASTER] - Add client to players list
static void	_event_client_new(t_B *back, t_matchmaking *matchmaking, t_msg *msg)
{
	int			id;
	t_info		*info;

	if (back->proc->info.is_master == false)
		return ;
	matchmaking->size += 1;
	id = *(int *)(msg->buff + 1);
	info = (t_info *)msg->buff + 1 + sizeof(int);
	_add_player(back, matchmaking, id, info);
}

//[MASTER] - Remove client to players list
static void	_event_client_del(t_B *back, t_matchmaking *matchmaking, t_msg *msg)
{
	int			id;
	t_list		*node;
	t_player	*player;

	if (back->proc->info.is_master == false)
		return ;
	id = *(int *)(msg->buff + 1);
	node = matchmaking->players;
	player = NULL;
	while (node)
	{
		player = node->content;
		if (player && player->id == id)
			break ;
		player = NULL;
		node = node->next;
	}
	if (player)
	{
		matchmaking->size -= 1;
		matchmaking->teams_size[player->info.team] -= 1;
		lst_delone(&node, free);
	}
	if (matchmaking->start)
		matchmaking->start = _check_match_conditions(back, matchmaking);
	B_id_release(back, msg);
}

//exits
static void	_event_client_quit(t_B *back, t_matchmaking *matchmaking, t_msg *msg)
{
	(void)matchmaking, (void)msg;
	debug_log(back->proc, "request quit..");
	back->power_on = false;
}

//[MASTER] - checks the conditions, then starts the game.
//[MASTER] - starts the game.
static void	_event_client_start(t_B *back, t_matchmaking *matchmaking, t_msg *msg)
{
	(void)msg;
	if (back->proc->info.is_master == true)
	{
		debug_log(back->proc, "frontend asked to start the game..");
		matchmaking->start = _check_match_conditions(back, matchmaking);
		if (matchmaking->start == true)
			debug_log(back->proc, "request accepted..");
		else
			msg_sendId(back->proc, MSGID_FRONT, MSGE_ERROR, (void *)"Invalid teams/size");
		return ;
	}
	matchmaking->start = true;
	debug_log(back->proc, "let's start!");
}

//[MASTER] - gives a new player a unique ID
static void	_event_client_ask_id(t_B *back, t_matchmaking *matchmaking, t_msg *msg)
{
	(void)matchmaking;
	if (back->proc->info.is_master == false)
		return ;
	B_id_reserve(back, msg);
}

static void	_event_none(t_B *back, t_matchmaking *matchmaking, t_msg *msg)
{
	(void)back, (void)msg, (void)matchmaking;
}
