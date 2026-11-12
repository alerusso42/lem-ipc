/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 18:29:15 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/12 22:08:56 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"

void	F_events_queue(t_F *front)
{
	t_list	*msg_node;

	msg_node = F_mutex_getNextMsg(front);
	while (msg_node)
	{
		//parse..
		F_mutex_delCurrMsg(front);
		msg_node = F_mutex_getNextMsg(front);
	}
}
