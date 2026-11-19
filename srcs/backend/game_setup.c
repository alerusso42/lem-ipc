/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 16:23:19 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/19 17:30:52 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/backend.h"

void	_map_init(t_grid *map, t_player *players, t_match *match);

void	B_setup_game(t_B *back)
{
	size_t	size;
	int		n_cli;

	if (back->proc->info.is_master == false)
		return ;
	debug_log(back->proc, "Trying to extend shared memory..");
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
}

void	B_stop(t_B *backend)
{
	free(backend->arr_id);
	backend->arr_id = NULL;
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

void	_map_init(t_grid *map, t_player *players, t_match *match)
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
}
