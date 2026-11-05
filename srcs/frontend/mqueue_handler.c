/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mqueue_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 21:27:39 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/05 22:20:14 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"

bool	_frontend_run(t_F *front);

int	F_thread_mqueue(void *data)
{
	t_F	*front;

	front = data;
	while (_frontend_run(front))
	{
		SDL_LockMutex(front->sdl.mutex);
		front->msg.mtype = 1;
		SDL_UnlockMutex(front->sdl.mutex);
		msgrcv(front->msg_fd, &front->msg, BUFF_LEN, 1, 0);
	}
	return (0);
}

bool	_frontend_run(t_F *front)
{
	bool	status;

	SDL_LockMutex(front->sdl.mutex);
	status = front->power_off;
	SDL_UnlockMutex(front->sdl.mutex);
	return (status);
}
