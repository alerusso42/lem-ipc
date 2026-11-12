/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 18:10:52 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/12 09:05:57 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"

/**
 * @brief updates the game clock, updates timers
 * 
 * @param front 
 */
void	T_time_update(t_F *front)
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
bool	T_time_checkTimer(t_F *front, int id)
{
	T_time_update(front);
	if (front->timers[id].curr > 0)
		return (false);
	front->timers[id].curr = (int64_t)front->timers[id].start;
	return (true);
}
