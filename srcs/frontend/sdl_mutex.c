/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_mutex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 18:36:50 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/11 19:26:57 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"

/**
 * F_mutex critical section: 
 * @brief this function calls other non thread-safe functions, 
 * 		managing lock/unlock.
 * 
 * @param front 
 * @param f int	(t_F *front);	//may return 0
 * @return int a copy of the data (default: zero) 
 */
int	F_mutexCs(t_F *front, int (*f)(t_F *))
{
	int	copy;

	SDL_LockMutex(front->sdl.mutex);
	copy = f(front);
	SDL_UnlockMutex(front->sdl.mutex);
	return (copy);
}

int	F_mutex_runCheck(t_F *front)
{
	return (front->power_on);	
}

int	F_mutex_runStop(t_F *front)
{
	front->power_on = false;
	return (0);	
}
