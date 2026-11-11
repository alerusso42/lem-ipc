/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 18:10:52 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/11 20:04:47 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"

/**
 * @brief updates the game clock
 * 
 * @param front 
 */
void	T_time_update(t_F *front)
{
	front->clock.curr = front->clock.start;
	front->clock.start = SDL_GetTicks();
	front->elapsed_time = front->clock.start - front->clock.curr;
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
	front->timers[id].curr -= front->elapsed_time;
	if (front->timers[id].curr > 0)
		return (false);
	front->timers[id].curr = (int64_t)front->timers[id].start;
	return (true);
}
