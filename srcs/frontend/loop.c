/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 17:21:52 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/11 20:56:51 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"

void	F_loop(t_F *front)
{
	while (F_mutexCs(front, F_mutex_runCheck))
	{
		T_time_update(front);
		if (T_time_checkTimer(front, TIM_FPS) == false)
		{
			// ft_printf("delay of %d\n", front->timers[TIM_FPS].start - front->timers[TIM_FPS].curr);;
			SDL_Delay(front->timers[TIM_FPS].curr);
			T_time_update(front);
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
