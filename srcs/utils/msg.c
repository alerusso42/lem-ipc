/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 16:27:03 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/16 17:32:08 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/setup.h"

void	msg_receive(t_data *data)
{
	t_list	*node;
	t_msg	*msg;

	lst_clear(&data->msg_list, free);
	while (msgrcv(data->msg_fd, &data->msg, BUFF_LEN, data->id, IPC_NOWAIT) > 0)
	{
		msg = malloc(sizeof(t_msg));
		if (!msg)
			return (error(data, "msg_receive alloc"));
		ft_memcpy(msg, &data->msg, sizeof(t_msg));
		node = lst_new(msg);
		if (!node)
			return (free(msg), error(data, "msg_receive alloc"));
		lst_back(&data->msg_list, node);
	}
}

void	msg_sendId(t_data *data, int id, int msg_type, void *ptr)
{
	(void)ptr;
	if (id == data->id)
		return ;
	data->msg.mtype = id;
	data->msg.buff[0] = msg_type;
	if (msgsnd(data->msg_fd, &data->msg, BUFF_LEN, IPC_NOWAIT) == -1)
		error(data, "msgsnd failure");
	data->msg.mtype = data->id;
}

void	msg_sendAll(t_data *data, int msg_type, void *ptr)
{
	int	n_client;

	if (!data->shared)
		return ;
	sem_wait(&data->shared->sem);
	n_client = data->shared->n_client;	
	sem_post(&data->shared->sem);
	for (int i = 1; i != n_client; i++)
		msg_sendId(data, i, msg_type, ptr);
}
