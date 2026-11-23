/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_timer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 20:03:45 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/23 10:04:48 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/backend.h"

//SECTION - defines

#define TIMERS_B_TIME	\
(const int [])\
{\
	[TIMB_MATCHMAKING] = 30000e3, \
	[TIMB_TEST] = 1000e3, \
	[TIMB_NUM] = 0 \
}

static void	B_timeHandler_test(t_B *back);
static void	B_timeHandler_matchmaking(t_B *back);

#define TIMERS_B_HANDLER	\
(void (*[])(t_B*))\
{\
	[TIMB_MATCHMAKING] = B_timeHandler_matchmaking, \
	[TIMB_TEST] = B_timeHandler_test, \
	[TIMB_NUM] = NULL \
}

//SECTION - init

void	B_timer_start(t_B *back)
{
	for (int i = 0; i != TIMB_NUM; i++)
	{
		timer_init(&back->timers[i], TIMERS_B_TIME[i], \
		(void *)TIMERS_B_HANDLER[i], back);
	}
}

static void	B_timeHandler_test(t_B *back)
{
	(void)back;
	debug_log_int(back->proc, "time left after a second: %d milliseconds", back->timers[TIMB_MATCHMAKING]._curr / 1000);
}

static void	B_timeHandler_matchmaking(t_B *back)
{
	debug_log(back->proc, "Matchmaking timer's up");
	back->timeout_matchmaking = true;
}
