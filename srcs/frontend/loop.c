/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 17:21:52 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/26 15:50:41 by alerusso         ###   ########.fr       */
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
		if (front->info.is_playing == true)
			F_render_grid(front);
		SDL_RenderPresent(front->sdl.renderer);
	}
}
