/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mqueue_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 21:27:39 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/11 19:57:04 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"

bool	_frontend_run(t_F *front);

int	F_thread_mqueue(void *data)
{
	t_F	*front;

	front = data;
	while (F_mutexCs(front, F_mutex_runCheck))
	{
		msgrcv(front->msg_fd, &front->msg, BUFF_LEN, 1, 0);
	}
	return (0);
}
