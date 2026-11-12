/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 17:21:52 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/12 09:22:52 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"

void	F_loop(t_F *front)
{
	while (F_mutexCs(front, F_mutex_runCheck))
	{
		if (T_time_checkTimer(front, TIM_FPS) == false)
		{
			SDL_Delay(front->timers[TIM_FPS].curr);
			front->timers[TIM_FPS].curr = front->timers[TIM_FPS].start;
		}
		if (T_time_checkTimer(front, TIM_SECOND) == true)
		{
			ft_printf("$YFPS$Z: %d\n", front->fps);
			front->fps = 0;
		}
		else
			front->fps++;
		if (T_time_checkTimer(front, TIM_TEST) == true)
		{
			F_mutexCs(front, F_mutex_runStop);
			break ;
		}
	}
}
