/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_timer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 20:03:45 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/22 20:15:20 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/backend.h"

//SECTION - defines

#define TIMERS_TIME	\
(const int [])\
{\
	[TIMB_TEST] = 5000e3, \
	[TIMB_NUM] = 0 \
}

static void	B_timeHandler_test(t_B *back);

#define TIMERS_HANDLER	\
(void (*[])(t_B*))\
{\
	[TIMB_TEST] = B_timeHandler_test, \
	[TIMB_NUM] = NULL \
}

//SECTION - init

void	B_timer_start(t_B *back)
{
	for (int i = 0; i != TIMB_NUM; i++)
	{
		timer_init(&back->timers[i], TIMERS_TIME[i], \
		(void *)TIMERS_HANDLER[i], back);
	}
	back->timers[TIMB_NUM].reverse_activation = true;
}

static void	B_timeHandler_test(t_B *back)
{
	(void)back;
	debug_log(back->proc, "test");
}
