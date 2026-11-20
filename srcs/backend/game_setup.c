/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 16:23:19 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/20 12:09:27 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/backend.h"

static void	_map_init(t_grid *map, t_player *players, t_match *match);
static void	_create_midwalls(t_grid *map, t_match *match);
// static void	_players_init(t_grid *map, t_player *players, t_match *match);

void	B_stop(t_B *backend)
{
	free(backend->arr_id);
	backend->arr_id = NULL;
	lst_clear(&backend->players_start_info, free);
	cleanup(backend->proc);
}

void	B_error(t_B *backend, const char *err)
{
	backend->proc->info.error = true;
	debug_log(backend->proc, err);
	error(backend->proc, NULL);
}

void	B_sigint(int sig)
{
	(void)sig;
	global_sigint = true;	
}

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

	if (back->proc->info.is_master == false)
	{
		debug_log(back->proc, "Extending mmap ptr..");
		if (shm_update(back->proc) == false)	
			B_error(back, "cannot reset mmap ptr");
		return ;
	}
	debug_log(back->proc, "Extending shared memory..");
	sem_wait(&back->proc->shared->s_gen);
	n_cli = back->proc->shared->n_client;
	sem_post(&back->proc->shared->s_gen);
	back->proc->shared->match.map_x = n_cli * INFO_MAP_X;
	back->proc->shared->match.map_y = n_cli * INFO_MAP_Y;
	size = back->proc->shared->match.map_x * back->proc->shared->match.map_y;
	back->proc->shared->match.map_area = size;
	size *= sizeof(t_grid);//size is now the memory for the game map
	back->proc->shared->offset_player = size;
	size += (n_cli * (sizeof(t_player)));//size is now shared memory heap buff
	if (shm_extend(back->proc, size) == false)
		B_error(back, "cannot extend shared memory");
	debug_log(back->proc, "Creating and populating the game grid..");
	back->proc->map = (t_grid *)back->proc->shared->heap;
	back->proc->players = \
	(t_player *)(back->proc->shared->heap + back->proc->shared->offset_player);
	back->proc->players[n_cli].id = -1;
	_map_init(back->proc->map, back->proc->players, &back->proc->shared->match);
	
	msg_sendAll(back->proc, MSGE_START, NULL);
	lst_clear(&back->players_start_info, free);
}

static void	_map_init(t_grid *map, t_player *players, t_match *match)
{
	(void)players;
	match->map_topl = 0;
	match->map_topr = match->map_x - 1;
	match->map_botl = match->map_area - match->map_x;
	match->map_botr = match->map_area - 1;
	for (int i = match->map_topl; i <= match->map_topr; i++)
		map[i].val = SQ_WALL;
	for (int i = match->map_botl; i <= match->map_botr; i++)
		map[i].val = SQ_WALL;
	for (int i = match->map_topl; i <= match->map_botl; i += match->map_x)
		map[i].val = SQ_WALL;
	for (int i = match->map_topr; i <= match->map_botr; i += match->map_x)
		map[i].val = SQ_WALL;
	_create_midwalls(map, match);
	// _players_init();
}

static void	_create_midwalls(t_grid *map, t_match *match)
{
	bool	is_left_wall;

	match->wall_offx_r = ((float)match->map_x / INFO_WALLMID_X);
	match->wall_offy_r = (((float)match->map_y / INFO_WALLMID_Y) + 0.5);
	match->wall_bot_r = match->wall_offx_r + (match->map_x * match->wall_offy_r);
	match->wall_top_r = match->map_area - match->wall_offx_r - (match->map_x * match->wall_offy_r);
	if (match->wall_top_r < 0)
		match->wall_top_r = 0; 
	if (!match->wall_top_r || !match->wall_bot_r)
		return ;
	match->wall_bot_l = match->wall_bot_r;
	match->wall_top_l = match->wall_top_r;
	match->wall_offx_l = match->wall_offx_r;
	match->wall_offy_l = match->wall_offy_r;
	is_left_wall = false;
	if (match->map_x % 2 == 0)
	{
		match->wall_bot_l--;
		match->wall_top_l--;
		match->wall_offx_l--;
		match->wall_offy_l--;
		is_left_wall = true;
	}
	for (int i = match->wall_bot_r; i <= match->wall_top_r; i += match->map_x)
	{
		map[i - is_left_wall].val = SQ_WALL;
		map[i].val = SQ_WALL;
	}
}

// static void	_players_init(t_grid *map, t_player *players, t_match *match)
// {
// 	(void)map, (void)players, (void)match;
// }
