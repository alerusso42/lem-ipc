/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 17:21:52 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/22 18:53:40 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"

void	F_loop(t_F *front)
{
	while (front->power_on == true)
	{
		timer_checkAll(front->timers, TIM_NUM);
		F_events_queue(front);
		F_events_sdl(front);
		SDL_RenderPresent(front->sdl.renderer);
	}
}
