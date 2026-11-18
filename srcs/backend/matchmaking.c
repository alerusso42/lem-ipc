/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matchmaking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 16:05:59 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/18 09:54:01 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/backend.h"

static int	_check_match_conditions(t_B *back, t_MatchMaking *matchmaking);
static void	_shuffle_teams(t_MatchMaking *matchmaking);
static int	_find_littlest_team(t_MatchMaking *matchmaking);
static void	_event_client_new(t_B *back, t_MatchMaking *matchmaking, t_msg *msg);
static void	_event_client_del(t_B *back, t_MatchMaking *matchmaking, t_msg *msg);
static void	_event_client_quit(t_B *back, t_MatchMaking *matchmaking, t_msg *msg);
static void	_event_client_start(t_B *back, t_MatchMaking *matchmaking, t_msg *msg);
static void	_event_none(t_B *back, t_MatchMaking *matchmaking, t_msg *msg);

#define EVENTS_HANDLER \
(void (*[])(t_B*, t_MatchMaking*, t_msg*))\
{\
	[MSGE_INVALID] = _event_none,\
	[MSGE_CLIENT_NEW] = _event_client_new,\
	[MSGE_CLIENT_DEL] = _event_client_del,\
	[MSGE_QUIT] = _event_client_quit,\
	[MSGE_START] = _event_client_start,\
	[MSGE_NUM] = _event_none\
}

void	B_matchmaking(t_B *back)
{
	int				tries;
	t_msg			*msg;
	t_MatchMaking	matchmaking;

	matchmaking = (t_MatchMaking){0};
	matchmaking.size = 1;
	tries = 18;
	while (back->power_on == true && matchmaking.start == false && tries-- > 0)
	{
		msg_receive(back->proc);
		while (back->proc->msg_list)
		{
			msg = back->proc->msg_list->content;
			if (msg && *(msg->buff) > MSGE_INVALID && *(msg->buff) < MSGE_NUM)
				EVENTS_HANDLER[(int)*(msg->buff)](back, &matchmaking, msg);
			lst_delone(&back->proc->msg_list, free);
		}
		usleep(5e5);
	}
	if (matchmaking.start == true)
	{
		if (back->proc->info.is_master)
		{
			msg_sendAll(back->proc, MSGE_START, NULL);
			debug_log(back->proc, "matchmaking done.");
		}
		return ;
	}
	//TODO - B_cleanup
	cleanup(back->proc);
	exit(0);
}

static int	_check_match_conditions(t_B *back, t_MatchMaking *matchmaking)
{
	bool	try_shuffle;

	try_shuffle = false;
	if (matchmaking->size < back->proc->num_players)
		return (false);
	for (int i = 1; i != INFO_TEAM_NUM; i++)
		if (matchmaking->teams_size[0] != matchmaking->teams_size[i])
			try_shuffle = true;
	if (try_shuffle == false)
		return (true);
	_shuffle_teams(matchmaking);
	for (int i = 1; i != INFO_TEAM_NUM; i++)
		if (matchmaking->teams_size[0] != matchmaking->teams_size[i])
			return (false);
	return (true);
}

static void	_shuffle_teams(t_MatchMaking *matchmaking)
{
	int			team;
	t_list		*node;
	t_player	*player;

	team = _find_littlest_team(matchmaking);
	node = matchmaking->players;
	while (node)
	{
		player = node->content;
		if (player && player->info.is_team_lock == false && player->info.team != team)
		{
			matchmaking->teams_size[player->info.team] -= 1;
			matchmaking->teams_size[team] += 1;
			player->info.team = team;
			team = _find_littlest_team(matchmaking);
		}
		node = node->next;
	}
}

static int	_find_littlest_team(t_MatchMaking *matchmaking)
{
	int	littlest;

	littlest = 0;
	for (int i = 0; i != INFO_TEAM_NUM; i++)
	{
		if (matchmaking->teams_size[littlest] > matchmaking->teams_size[i])
			littlest = i;
	}
	return (littlest);
}

static void	_event_client_new(t_B *back, t_MatchMaking *matchmaking, t_msg *msg)
{
	int			id;
	t_info		*info;
	t_list		*node;

	if (back->proc->info.is_master == false)
		return ;
	matchmaking->size += 1;
	id = *(int *)msg->buff + 1;
	info = (t_info *)msg->buff + 1 + sizeof(int);
	node = lst_new(ft_calloc(1, sizeof(t_player)));
	if (!node)
		error(back->proc, "malloc: can't create node for matchmaking");
	lst_back(&matchmaking->players, node);
	((t_player *)node->content)->id = id;
	((t_player *)node->content)->info = *info;
	matchmaking->teams_size[info->team] += 1;
	matchmaking->start = _check_match_conditions(back, matchmaking);
}

static void	_event_client_del(t_B *back, t_MatchMaking *matchmaking, t_msg *msg)
{
	int			id;
	t_list		*node;
	t_player	*player;

	if (back->proc->info.is_master == false)
		return ;
	id = *(int *)msg->buff + 1;
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
}

static void	_event_client_quit(t_B *back, t_MatchMaking *matchmaking, t_msg *msg)
{
	(void)matchmaking, (void)msg;
	if (back->proc->info.is_master == true)
		return ;
	back->power_on = false;
}

static void	_event_client_start(t_B *back, t_MatchMaking *matchmaking, t_msg *msg)
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

static void	_event_none(t_B *back, t_MatchMaking *matchmaking, t_msg *msg)
{
	(void)back, (void)msg, (void)matchmaking;
}
