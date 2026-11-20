/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 10:52:17 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/20 12:33:18 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem-ipc.h"

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
