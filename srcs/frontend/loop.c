/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 17:21:52 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/14 20:06:29 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"

void	F_loop(t_F *front)
{
	while (F_mutexCs(front, F_mutex_runCheck))
	{
		if (F_time_checkTimer(front, TIM_FPS) == false)
		{
			F_time_waitTimer(front, TIM_FPS);
		}
		if (F_time_checkTimer(front, TIM_SECOND) == true)
		{
			ft_printf("$YFPS$Z: %d\n", front->fps);
			front->fps = 0;
		}
		else
			front->fps++;
		if (F_time_checkTimer(front, TIM_TEST) == true)
		{
			F_mutexCs(front, F_mutex_runStop);
			break ;
		}
		F_events_queue(front);
	}
}
