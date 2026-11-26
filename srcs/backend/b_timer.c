/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_timer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 20:03:45 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/26 13:29:04 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/backend.h"

//SECTION - defines

#define TIMERS_B_TIME	\
(const int [])\
{\
	[TIMB_MATCHMAKING] = 30e6, \
	[TIMB_BFS] = 1e6, \
	[TIMB_MOVE] = (GAME_SPEED / SQUARE_DENSITY), \
	[TIMB_MOVE_PUSH] = GAME_SPEED / 2, \
	[TIMB_MOVE_STUN] = GAME_SPEED * 3, \
	[TIMB_TEST] = 1000e3, \
	[TIMB_NUM] = 0 \
}

static void	B_timeHandler_matchmaking(t_B *back);
static void	B_timeHandler_bfs(t_B *back);
static void	B_timeHandler_move(t_B *back);
static void	B_timeHandler_move_push(t_B *back);
static void	B_timeHandler_move_stun(t_B *back);
static void	B_timeHandler_test(t_B *back);

#define TIMERS_B_HANDLER	\
(void (*[])(t_B*))\
{\
	[TIMB_MATCHMAKING] = B_timeHandler_matchmaking, \
	[TIMB_MOVE] = B_timeHandler_move, \
	[TIMB_MOVE_PUSH] = B_timeHandler_move_push, \
	[TIMB_MOVE_STUN] = B_timeHandler_move_stun, \
	[TIMB_BFS] = B_timeHandler_bfs, \
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
		back->timers[i].freeze = true;
	}
	back->timers[TIMB_TEST].freeze = false;
}

static void	B_timeHandler_matchmaking(t_B *back)
{
	debug_log(back->proc, "Matchmaking timer's up");
	back->timeout_matchmaking = true;
}

static void	B_timeHandler_bfs(t_B *back)
{
	debug_log(back->proc, "bfs update");
}

static void	B_timeHandler_move(t_B *back)
{
	(void)back;
	debug_log(back->proc, "MOVEMENT");
}

static void	B_timeHandler_move_push(t_B *back)
{
	debug_log(back->proc, "MOVE PUSH");
}

static void	B_timeHandler_move_stun(t_B *back)
{
	debug_log(back->proc, "STUN ENDED");
	back->timers[TIMB_MOVE_STUN].freeze = true;
	timer_reset(&back->timers[TIMB_MOVE]);
}

static void	B_timeHandler_test(t_B *back)
{
	(void)back;
	debug_log_int(back->proc, "time left after a second: %d milliseconds", back->timers[TIMB_MATCHMAKING]._curr / 1000);
}
