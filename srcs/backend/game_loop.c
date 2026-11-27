/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 10:32:06 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/27 11:26:25 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/backend.h"

void	B_game_loop(t_B *back)
{
	timer_reset(&back->timers[TIMB_MOVE]);
	while (back->power_on)
	{
		timer_checkAll(back->timers, TIMB_NUM);
		B_game_msg(back);
		usleep(WAIT_GAME);
	}
}
