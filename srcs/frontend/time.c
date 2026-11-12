/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 18:10:52 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/12 21:12:39 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"

/**
 * @brief updates the game clock, updates timers
 * 
 * @param front 
 */
void	F_time_update(t_F *front)
{
	uint64_t	elapsed;

	front->clock.curr = front->clock.start;
	front->clock.start = SDL_GetTicks();
	elapsed = front->clock.start - front->clock.curr;
	for (int i = 0; i != TIM_NUM; i++)
		front->timers[i].curr -= elapsed;
}

/**
 * @brief check if an event's timer has expired. If true, resets the timer
 * 
 * @param front 
 * @param id id of the timer
 * @return true if the timer has expired
 * @return false otherwise
 */
bool	F_time_checkTimer(t_F *front, int id)
{
	F_time_update(front);
	if (front->timers[id].curr > 0)
		return (false);
	front->timers[id].curr = front->timers[id].start - front->timers[id].curr;
	return (true);
}

/**
 * @brief wait for a timer to end. Reset that timer.
 * 
 * @param front 
 * @param id 
 */
void	F_time_waitTimer(t_F *front, int id)
{
	SDL_Delay(front->timers[id].curr);
	F_time_update(front);
	front->timers[id].curr = front->timers[id].start;
}
