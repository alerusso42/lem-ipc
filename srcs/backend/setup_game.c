/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 16:23:19 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/28 14:48:01 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/backend.h"

static void	_shm_get_heap_ptr(t_B *back);
static void	_map_init(t_B *back);
static void	_create_midwalls(t_grid *map, t_match *match);
static void	_players_init(t_B *back);
static void	_map_add_players(t_B *back);

/**
 * @brief setups the game shared resources: map, player array.
 * 
 * ```md
 * Steps:
 * 1. Calculate the exact size needed and the offset between them;
 * 2. Extends shared memory: allocs a char buffer (a heap) for new resources;
 * 3. Populates map, filling boards with walls;
 * 4. Populates player array.
 * the setups is managed differently between master and client:
 * | MSG event    | Master                                 | Client
 * | -------------| -------------------------------------- | ------
 * | CLIENT_NEW   | Add client to players list             | -
 * ```
 * 
 * @param back 
 */
void	B_setup_game(t_B *back)
{
	size_t	size;
	int		n_cli;
	int		map_len;

	if (back->proc->info.is_ai == false)
		back->proc->info.move_stop = true;
	if (back->proc->info.is_master == false)
	{
		debug_log(back->proc, "Extending mmap ptr..");
		if (shm_update(back->proc) == false)	
			B_error(back, "cannot reset mmap ptr");
		_shm_get_heap_ptr(back);
		B_id_player(back);
		return ;
	}
	debug_log(back->proc, "Extending shared memory..");
	sem_wait(&back->proc->shared->s_gen);
	n_cli = back->proc->shared->n_client;
	sem_post(&back->proc->shared->s_gen);
	map_len = n_cli <= 3 ? n_cli + 1 : n_cli;
	back->proc->shared->match.map_x = map_len * INFO_MAP_X;
	back->proc->shared->match.map_y = map_len * INFO_MAP_Y;
	size = back->proc->shared->match.map_x * back->proc->shared->match.map_y;
	back->proc->shared->match.map_area = size;
	size *= sizeof(t_grid);//size is now the memory for the game map
	back->proc->shared->offset_player = size;
	size += (n_cli * (sizeof(t_player)));//size is now shared memory heap buff
	if (shm_extend(back->proc, size) == false)
		B_error(back, "cannot extend shared memory");
	_shm_get_heap_ptr(back);
	debug_log(back->proc, "Creating and populating the game grid..");
	_players_init(back);
	_map_init(back);
	msg_sendAll(back->proc, MSGE_START, NULL);
}

static void	_shm_get_heap_ptr(t_B *back)
{
	char	*heap;

	heap = back->proc->shared->heap;
	back->map = (t_grid *)heap;
	back->players = (t_player *)(heap + back->proc->shared->offset_player);
	back->match = &back->proc->shared->match;
	back->proc->map = back->map;
	back->proc->players = back->players;
}

static void	_players_init(t_B *back)
{
	int			p_idx;
	t_player	*player;

	for (int i = 0; i != INFO_TEAM_NUM; i++)
		back->match->team_offset[i] = INFO_PLAYER_END;
	back->match->player_num = lst_size(back->players_start_info);
	p_idx = 0;
	back->match->team_offset[0] = 0;
	for (int id_team = 0; id_team != back->proc->info.num_team; id_team++)
	{
		for (t_list *p_node = back->players_start_info; p_node != NULL; p_node = p_node->next)
		{
			player = (t_player *)p_node->content;
			if (player == NULL)
				continue ;
			if (back->proc->id == player->id)
				back->id_player = p_idx;
			if (player->info.team == id_team)
				back->players[p_idx++] = *player;
		}
		back->match->team_offset[id_team + 1] = p_idx; 
	}
	back->players[p_idx].id = -1;
	lst_clear(&back->players_start_info, free);
}

static void	_map_init(t_B *back)
{
	t_grid	*map;
	t_match	*match;

	map = back->map;
	match = back->match;
	match->map_topl = 0;
	match->map_topr = match->map_x - 1;
	match->map_botl = match->map_area - match->map_x;
	match->map_botr = match->map_area - 1;
	for (int i = 0; i != match->map_area; i++)
	{
		map[i].val = SQ_FREE;
		for (int j = 0; j != INFO_TEAM_NUM; j++)
			map[i].ids[j] = INFO_PLAYER_NONE;
	}
	for (int i = match->map_topl; i <= match->map_topr; i++)
		map[i].val = SQ_WALL;
	for (int i = match->map_botl; i <= match->map_botr; i++)
		map[i].val = SQ_WALL;
	for (int i = match->map_topl; i <= match->map_botl; i += match->map_x)
		map[i].val = SQ_WALL;
	for (int i = match->map_topr; i <= match->map_botr; i += match->map_x)
		map[i].val = SQ_WALL;
	_create_midwalls(map, match);
	_map_add_players(back);
	if (grid_copy(back->proc, &back->map_copy) == false)
		B_error(back, "Cannot copy the grid");
}

static void	_create_midwalls(t_grid *map, t_match *match)
{
	bool	is_left_wall;

	match->wall_off_r.x = ((float)match->map_x / INFO_WALLMID_X);
	match->wall_off_r.y = (((float)match->map_y / INFO_WALLMID_Y) + 0.5) + 1;
	match->wall_bot_r = match->wall_off_r.x + (match->map_x * match->wall_off_r.y);
	match->wall_top_r = match->map_area - match->wall_off_r.x - (match->map_x * match->wall_off_r.y);
	if (match->wall_top_r < 0)
		match->wall_top_r = 0;
	if (!match->wall_top_r || !match->wall_bot_r)
		return ;
	match->wall_bot_l = match->wall_bot_r;
	match->wall_top_l = match->wall_top_r;
	match->wall_off_l.x = match->wall_off_r.x;
	match->wall_off_l.y = match->wall_off_r.y;
	is_left_wall = false;
	if (match->map_x % 2 == 0)
	{
		match->wall_bot_l--;
		match->wall_top_l--;
		match->wall_off_l.x--;
		match->wall_off_l.y--;
		is_left_wall = true;
	}
	for (int i = match->wall_bot_r; i <= match->wall_top_r; i += match->map_x)
	{
		map[i - is_left_wall].val = SQ_WALL;
		map[i].val = SQ_WALL;
	}
}

static void	_map_add_players(t_B *back)
{
	int	spawn_coord[INFO_TEAM_NUM];
	int	spawn_offset[INFO_TEAM_NUM];
	int	id_team;
	int	last_team;
	int	coord;

	spawn_coord[INFO_TEAM_RED] = back->match->map_x + 1;
	spawn_coord[INFO_TEAM_YELLOW] = (back->match->map_x * 2) - 2;
	spawn_coord[INFO_TEAM_GREEN] = back->match->map_area - spawn_coord[INFO_TEAM_RED] - 1;
	spawn_coord[INFO_TEAM_BLUE] = back->match->map_area - spawn_coord[INFO_TEAM_YELLOW] - 1;
	spawn_offset[INFO_TEAM_RED] = INFO_MAP_X;
	spawn_offset[INFO_TEAM_YELLOW] = back->match->map_x * INFO_MAP_X;
	spawn_offset[INFO_TEAM_GREEN] = -spawn_offset[INFO_TEAM_RED];
	spawn_offset[INFO_TEAM_BLUE] = back->match->map_x * -INFO_MAP_X;
	last_team = -1;
	coord = 0;
	for (int i = 0; i != back->match->player_num; i++)
	{
		id_team = back->players[i].info.team;
		if (id_team != last_team)
		{
			last_team = id_team;
			coord = spawn_coord[id_team];
		}
		else
			coord += spawn_offset[id_team];
		back->map[coord].ids[0] = back->players[i].id;
		back->map[coord].val = back->players[i].info.team;
		for (int j = 1; j != KART_MAX_SQUARE; j++)
			back->players[i].map_id[j] = -1;
		back->players[i].map_id[0] = coord;
		back->players[i].edge.x = INFO_SPRITE_SIZE / 2;
		back->players[i].edge.y = INFO_SPRITE_SIZE / 2;
	}
}
