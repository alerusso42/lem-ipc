/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kart_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 11:34:27 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/28 15:37:11 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/backend.h"

static void	_change_square(t_fcoord *edge, int *mask);

void	B_kart_move(t_B *back)
{
	t_fcoord	old_edge;
	t_fcoord	new_edge;
	float		chunk;
	int			update_mask;

	if (back->proc->info.move_dead || back->proc->info.move_stop || back->proc->info.move_stun)
		return ;
	sem_wait(&back->proc->shared->s_player);
	old_edge = back->players[back->id_player].edge;
	sem_post(&back->proc->shared->s_player);
	new_edge = old_edge;
	chunk = back->match->move_chunk;
	if (back->proc->info.move_dir & MOVE_REVERSE)
		chunk *= -1;
	if (back->proc->info.move_dir & MOVE_X)
		new_edge.x += chunk;
	else if (back->proc->info.move_dir & MOVE_Y)
		new_edge.y += chunk;
	update_mask = 0;
	_change_square(&new_edge, &update_mask);
	//continue
}

static void	_change_square(t_fcoord *edge, int *mask)
{
	if (edge->x < 0)
	{
		edge->x = INFO_SPRITE_SIZE - edge->x;
		*mask |= MOVE_EAST;
		*mask |= (MOVE_WEST << SQUARE_DELETE);
	}
	else if (edge->x >= INFO_SPRITE_SIZE)
	{
		edge->x = 0 + (edge->x - INFO_SPRITE_SIZE);
		*mask |= MOVE_WEST;
		*mask |= (MOVE_EAST << SQUARE_DELETE);
	}
	else if (edge->y < 0)
	{
		edge->y = INFO_SPRITE_SIZE - edge->y;
		*mask |= MOVE_NORTH;
		*mask |= (MOVE_SOUTH << SQUARE_DELETE);
	}
	else if (edge->y >= INFO_SPRITE_SIZE)
	{
		edge->y = 0 + (edge->y - INFO_SPRITE_SIZE);
		*mask |= MOVE_SOUTH;
		*mask |= (MOVE_NORTH << SQUARE_DELETE);
	}
}
