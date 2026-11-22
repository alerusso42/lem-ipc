/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timers_f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 18:10:52 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/22 17:20:41 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"
#include <time.h>

static int	_time_getnow(uint64_t *time_ptr);

//SECTION - general functions

void	timer_checkAll(t_timer *timers, int64_t nmemb)
{
	if (nmemb <= 0 || !timers)
		return ;
	for (int i = 0; i != nmemb; i++)
		timer_check(&timers[i]);
}

/**
 * @brief check if an event's timer has expired. If true, resets the timer
 * 
 * @param front 
 * @param id id of the timer
 * @return true if the timer has expired
 * @return false otherwise
 */
void	timer_check(t_timer *timer)
{
	uint64_t	time_now;

	if (_time_getnow(&time_now) != 0)
		return ;
	timer->_curr -= (int64_t)(time_now - timer->_time);
	timer->_time = time_now;
	if (timer->_curr > 0)
	{
		if (timer->reverse_activation == true && timer->handler)
			timer->handler(timer->data);
		return ;
	}
	timer->_curr = timer->start - timer->_curr;
	if (timer->reverse_activation == false && timer->handler)
		timer->handler(timer->data);
}

void	timer_init(t_timer *timer, int64_t start, void (*handler)(void*), void *data)
{
	if (!timer)
		return ((void)write(2, "timer error: tim ptr is NULL\n", 29));
	timer->start = start;
	timer->_curr = start;
	_time_getnow(&timer->_time);
	timer->reverse_activation = false;
	timer->handler = handler;
	timer->data = data;
}

void	time_reset(t_timer *timer)
{
	if (_time_getnow(&timer->_time) == 1)
		return ;
	timer->_curr = timer->start;
}

//SECTION - utilities

static int	_time_getnow(uint64_t *time_ptr)
{
	struct timeval	time_raw;

	if (gettimeofday(&time_raw, NULL) != 0)
		return (write(2, "WARNING, time: gettimeofday failed\n", 35), 1);
	*time_ptr = (time_raw.tv_sec * 1e6) + time_raw.tv_usec;
	return (0);
}

//SECTION - specific handlers

void	F_timeHandler_fps(t_F *front)
{
	t_timer	*timer;

	timer = &front->timers[TIM_FPS];
	usleep(timer->_curr);
	time_reset(timer);
	front->fps_count++;
}

void	F_timeHandler_second(t_F *front)
{
	front->fps = front->fps_count;
	front->fps_count = 0;
	debug_log_int(front->proc, "$YFPS$Z: %d", front->fps);
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
