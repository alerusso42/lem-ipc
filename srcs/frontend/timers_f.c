// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   timers_f.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2026/11/11 18:10:52 by alerusso42        #+#    #+#             */
// /*   Updated: 2026/11/22 14:12:20 by alerusso42       ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/frontend.h"
// #include <time.h>

// static void	_time_update(t_F *front);

// //SECTION - general functions

// void	time_checkAllTimers(t_timer *timers, int64_t nmemb)
// {
// 	bool	ready;

// 	if (nmemb <= 0 || !timers)
// 		return ;
// 	for (int i = 0; i != nmemb; i++)
// 	{
// 		ready = F_time_checkTimer(front, &timers[i]);
// 		if (!front->timers[i].handler)
// 			continue ;
// 		if ((ready == true) == (i != TIM_FPS))
// 			timer->handler(front);
// 	}
// }

// /**
//  * @brief check if an event's timer has expired. If true, resets the timer
//  * 
//  * @param front 
//  * @param id id of the timer
//  * @return true if the timer has expired
//  * @return false otherwise
//  */
// bool	F_time_checkTimer(t_F *front, t_timer *timer)
// {
// 	_time_update(front);
// 	if (timer->curr > 0)
// 		return (false);
// 	timer->curr = timer->start - timer->curr;
// 	return (true);
// }

// void	time_init_clock(int64_t prescaler)
// {
	
// }

// void	time_init_timers(t_timer *timers, int64_t nmemb)
// {
	
// }

// void	time_usleep(uint8_t microseconds)
// {
	
// }

// //SECTION - utilities

// /**
//  * @brief updates the game clock, updates timers
//  * 
//  * @param front 
//  */
// static void	_time_update(t_timer *timers, int64_t nmemb)
// {
// 	struct timespec	time_raw;
// 	uint64_t		time_now;
// 	uint64_t		elapsed;

// 	if (clock_gettime(CLOCK_REALTIME, &time_raw) != 0)
// 		return ((void)write(2, "WARNING, time: gettimeofday failed\n", 35));
// 	time_now = (time_raw.tv_sec * 1e6) + time_raw.tv_usec;
// 	clock._curr = front->clock.start;
// 	clock.start = time_now;
// 	elapsed = clock.start - clock._curr;
// 	for (int i = 0; i != nmemb; i++)
// 	{
// 		elapsed = timers[i]._time;
// 		timers[i]._curr -= elapsed;
// 	}
// }

// //SECTION - specific handlers

// void	F_timeHandler_fps(t_F *front)
// {
// 	t_timer	*timer;

// 	timer = &front->timers[TIM_FPS];
// 	SDL_Delay(timer->curr);
// 	_time_update(front);
// 	timer->curr = timer->start;
// 	front->fps_count++;
// }

// void	F_timeHandler_second(t_F *front)
// {
// 	front->fps = front->fps_count;
// 	front->fps_count = 0;
// 	debug_log_int(front->proc, "$YFPS$Z: %d", front->fps);
// }

// void	F_timeHandler_endCheck(t_F *front)
// {
// 	bool	alone;

// 	sem_wait(&front->proc->shared->s_gen);
// 	alone = front->proc->shared->n_client <= 1; 
// 	sem_post(&front->proc->shared->s_gen);
// 	if (alone)
// 		front->power_on = false;
// }

// //one time handler to delay rendering
// void	F_timeHandler_firstRender(t_F *front)
// {
// 	F_render_reset(front);
// 	front->timers[TIM_RENDER].handler = NULL;
// }

// void	F_timeHandler_test(t_F *front)
// {
// 	(void)front;
// }
