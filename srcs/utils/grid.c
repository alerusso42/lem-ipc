/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 10:52:17 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/20 19:57:19 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem-ipc.h"

/**
 * @brief hard copy of the shared memory map (used to avoid locking 
 * 		semaphores every frame, slowing down the engine).
 * 
 * @param proc 
 * @param grid 
 * @return true if the copy succeed, 
 * @return false otherwise.
 */
bool	grid_copy(t_proc *proc, t_grid **grid)
{
	if (*grid)
		free(*grid);
	*grid = ft_calloc(1, proc->shared->offset_player);//heap[0] => heap[offset]
	if (!*grid)
		return (false);
	sem_wait(&proc->shared->s_map);
	ft_memcpy(*grid, proc->map, proc->shared->offset_player);
	sem_post(&proc->shared->s_map);
	return (true);
}

/**
 * @brief checks if the square in the coord is invalid or is a wall.
 * 
 * both external and internal walls are checked.
 * @param proc 
 * @param coord 
 * @return true if it's invalid or wall; 
 * @return false otherwise.
 */
bool	grid_issquare_wall(t_proc *proc, int coord)
{
	t_match	*match;
	int		coord_x;

	match = &proc->shared->match;
	if (coord <= 0 || coord >= match->map_area)//invalid coord
		return (true);
	coord_x = coord % match->map_x;
	if (coord_x == 0)//left side
		return (true);
	if (coord_x == (match->map_x - 1))//right side
		return (true);
	if (coord >= (match->map_area - match->map_x))//bot side
		return (true);
	if (coord < match->map_x)//top side
		return (true);
	if (!match->wall_bot_r)//stop if middle wall does not exist
		return (false);
	if (coord < match->wall_bot_l || coord > match->wall_top_r)//y mid wall check
		return (false);
	if (coord_x == match->wall_offx_r)//right middle wall
		return (true);
	if (coord_x == match->wall_offx_l)//left middle wall
		return (true);
	return (false);
}
