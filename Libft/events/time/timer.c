/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 18:10:52 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/26 13:21:51 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "timer.h"

static int	_time_getnow(int64_t *time_ptr);

//SECTION - general functions

/**
 * @brief t_timer constructor.
 * 
 * This function should be called before other timer_* functions.
 * Note that timers resolution is in microseconds.
 * 
 * #### additional variables:
 * 
 * The following variables may be set by the user AFTER
 * (and only AFTER) this function call:
 * ```md
 * - t_timer::reverse_activation: activate handler when timer is NOT expired.
 * ```
 * 
 * @param timer {t_timer *} a t_timer ptr
 * @param start {int64_t} time in microseconds before it expires and resets
 * @param handler {void (*)(void *)} optional handler to run when timer expires
 * @param data {void *} ptr to data given to the handler when run
 * @return 1 if gettimeofday fails, 
 * @return else 0 if succeed.
 * 
 * example of usage:
 * ```c
 * //assign timers an ID
 * enum	e_timer
 * {
 *	TIM_ONE,
 *	TIM_TWO,
 *	TIM_THREE,
 *	TIM_NUM
 * };
 * 
 * //assign time for each timer
 * #define TIM_TIME	\
 * (const int [])\
 * {\
 * 	[TIM_ONE] = 1000000, \
 * 	[TIM_TWO] = 2000000, \
 * 	[TIM_THREE] = 3000000, \
 * 	[TIM_NUM] = 0 \
 * }
 * 
 * void	handler_one(struct s_bar *);
 * void	handler_two(struct s_foo *);
 * 
 * //assign a handler
 * #define TIM_HANDLER	\
 * (void (*[])(void*))\
 * {\
 * 	[TIM_ONE] = handler_one, \
 * 	[TIM_TWO] = handler_two, \
 * 	[TIM_THREE] = NULL \
 * 	[TIM_NUM] = NULL \
 * }
 * 
 * //declare one or more timers
 * struct s_foo
 * {
 * 		t_timer	timers[TIM_NUM];
 * 		t_timer	another_timer;
 * 		//other data
 * }
 * 
 * //init the timers
 * void	bar(struct s_foo *data)
 * {
 * 		for (int i = 0; i != TIM_NUM; i++)
 * 		{
 * 			timer_init(&data->timers[i], TIM_TIME[i], \
 * 			(void *)TIM_HANDLER[i], data);
 *			}
 * 		timer_init(&data->another_timer, 1e6, foo, data);
 * }
 * ```
 * 
 */
int	timer_init(t_timer *timer, int64_t start, void (*handler)(void*), void *data)
{
	if (!timer)
		return (write(2, "timer error: tim ptr is NULL\n", 29), 1);
	timer->start = start;
	timer->_curr = start;
	_time_getnow(&timer->_time);
	timer->reverse_activation = false;
	timer->handler = handler;
	timer->data = data;
	return (0);
}

/**
 * @brief updates a timer, and execute its handler if expired.
 * 
 * if timer::reverse_activation is true, the handler is run when NOT expired.
 * Variable resetting is automatically done.
 * 
 * @param timer {t_timer *} a t_timer ptr initializated with timer_init
 * @return 1 if the timer has expired;  
 * @return 0 if it's not.  
 */
int	timer_check(t_timer *timer)
{
	int64_t	time_now;

	if (timer && timer->freeze == true)
		timer->_defreeze = true;
	if (!timer || timer->freeze == true || _time_getnow(&time_now) != 0)
		return (0);
	if (timer->_defreeze == false)
		timer->_curr -= (int64_t)(time_now - timer->_time);
	timer->_defreeze = timer->freeze;
	timer->_time = time_now;
	if (timer->_curr > 0)
	{
		if (timer->reverse_activation == true && timer->handler)
			timer->handler(timer->data);
		return (0);
	}
	timer->_curr = (timer->start + timer->_curr);
	if (timer->_curr < 0)
		timer->_curr = (timer->_curr % timer->start) * -1;
	if (timer->reverse_activation == false && timer->handler)
		timer->handler(timer->data);
	return (1);
}

/**
 * @brief calls timer_check through an array of timers
 * 
 * @param timers {t_timer **} array of timers
 * @param nmemb {int64_t} number of timers initializated with timer_init
 */
void	timer_checkAll(t_timer *timers, int64_t nmemb)
{
	if (nmemb <= 0 || !timers)
		return ;
	for (int i = 0; i != nmemb; i++)
	{
		timer_check(&timers[i]);
	}
}

/**
 * @brief reset timer without run the handler. Defreeze timer.
 * 
 * @param timer {t_timer *} {t_timer *} a t_timer ptr initializated with timer_init.
 */
void	timer_reset(t_timer *timer)
{
	if (_time_getnow(&timer->_time) == 1)
		return ;
	timer->_curr = timer->start;
	timer->freeze = false;
	timer->_defreeze = false;
}

//SECTION - utilities

//returns current time in microseconds
static int	_time_getnow(int64_t *time_ptr)
{
	struct timeval	time_raw;

	if (gettimeofday(&time_raw, NULL) != 0)
		return (write(2, "WARNING, time: gettimeofday failed\n", 35), 1);
	*time_ptr = (time_raw.tv_sec * 1e6) + time_raw.tv_usec;
	return (0);
}
