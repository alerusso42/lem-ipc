/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 17:38:16 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/24 16:40:40 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMER_H
# define TIMER_H

#include <sys/time.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

//SECTION - data struct

typedef struct s_timer
{
	int64_t	start;//time in microseconds before timer expires and resets
	void	(*handler)(void*);//handler that runs when timer expires 
	void	*data;//ptr to data given to the handler when is run
	int64_t	_curr;//internal counter that decrease from t_timer::start
	int64_t	_time;//last result of gettimeofday function call
	//[DEFAULT: 0], if true, handler is run when timer is NOT expired
	uint8_t	reverse_activation:1; 
}		t_timer;

//SECTION - function

int		timer_init(t_timer *timer, int64_t start, void (*handler)(void*), void *data);
int		timer_check(t_timer *timer);
void	timer_checkAll(t_timer *timers, int64_t nmemb);
void	timer_reset(t_timer *timer);

#endif