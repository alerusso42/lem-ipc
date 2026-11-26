/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 12:55:18 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/26 13:37:23 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/backend.h"

void	B_map_update(t_B *back)
{
	float	chunk;

	if (back->proc->info.move_stun)
		return (debug_log(back->proc, "WARNING: called map update stunned"));
	chunk = back->match->move_chunk;
	if (back->proc->info.move_push == true)
		chunk *= 2;
	debug_log(back->proc, "map update");
}
