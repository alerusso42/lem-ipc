/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 17:21:52 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/16 17:56:19 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"

void	F_loop(t_F *front)
{
	while (front->power_on == true)
	{
		F_time_checkAllTimers(front);
		F_events_queue(front);
	}
}
