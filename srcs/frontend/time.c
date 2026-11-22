/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 18:10:52 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/22 12:38:29 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"

static void	_time_update(t_F *front);

//SECTION - general functions

void	F_time_checkAllTimers(t_F *front)
{
	bool	ready;
	t_timer	*timer;

	for (int i = 0; i != TIM_NUM; i++)
	{
		timer = &front->timers[i];
		ready = F_time_checkTimer(front, timer);
		if (!front->timers[i].handler)
			continue ;
		if ((ready == true) == (i != TIM_FPS))
			timer->handler(front);
	}
}

/**
 * @brief check if an event's timer has expired. If true, resets the timer
 * 
 * @param front 
 * @param id id of the timer
 * @return true if the timer has expired
 * @return false otherwise
 */
bool	F_time_checkTimer(t_F *front, t_timer *timer)
{
	_time_update(front);
	if (timer->curr > 0)
		return (false);
	timer->curr = timer->start - timer->curr;
	return (true);
}

//SECTION - utilities

/**
 * @brief updates the game clock, updates timers
 * 
 * @param front 
 */
static void	_time_update(t_F *front)
{
	uint64_t	elapsed;

	front->clock.curr = front->clock.start;
	front->clock.start = SDL_GetTicks();
	elapsed = front->clock.start - front->clock.curr;
	if (!elapsed)
		return ;
	for (int i = 0; i != TIM_NUM; i++)
		front->timers[i].curr -= elapsed;
}

//SECTION - specific handlers

void	F_timeHandler_fps(t_F *front)
{
	t_timer	*timer;

	timer = &front->timers[TIM_FPS];
	SDL_Delay(timer->curr);
	_time_update(front);
	timer->curr = timer->start;
	front->fps_count++;
}

void	F_timeHandler_second(t_F *front)
{
	front->fps = front->fps_count;
	front->fps_count = 0;
	// debug_log_int(front->fps, "$YFPS$Z: %d", front->fps);
}

void	F_timeHandler_endCheck(t_F *front)
{
	bool	alone;

	sem_wait(&front->proc->shared->s_gen);
	alone = front->proc->shared->n_client <= 1; 
	sem_post(&front->proc->shared->s_gen);
	if (alone)
		front->power_on = false;
}

//one time handler to delay rendering
void	F_timeHandler_firstRender(t_F *front)
{
	F_render_reset(front);
	front->timers[TIM_RENDER].handler = NULL;
}

void	F_timeHandler_test(t_F *front)
{
	(void)front;
}
