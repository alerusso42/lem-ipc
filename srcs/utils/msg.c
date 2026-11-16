/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 16:27:03 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/16 20:21:32 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/backend.h"

static void	_parse_id(t_proc *proc, void *data);
static void	_parse_none(t_proc *proc, void *data);

#define MSG_PARSER \
(void (*[])(t_proc*, void*))\
{\
	[MSGE_INVALID] = _parse_none,\
	[MSGE_CLIENT_NEW] = _parse_id,\
	[MSGE_CLIENT_DEL] = _parse_id,\
	[MSGE_QUIT] = _parse_none,\
	[MSGE_NUM] = _parse_none\
}

/**
 * @brief saves in proc->msg_list a list with the received messages
 * 
 * @param proc 
 */
void	msg_receive(t_proc *proc)
{
	t_list	*node;
	t_msg	*msg;

	lst_clear(&proc->msg_list, free);
	while (msgrcv(proc->msg_fd, &proc->msg, BUFF_LEN, proc->id, IPC_NOWAIT) > 0)
	{
		msg = malloc(sizeof(t_msg));
		if (!msg)
			return (error(proc, "msg_receive alloc"));
		ft_memcpy(msg, &proc->msg, sizeof(t_msg));
		node = lst_new(msg);
		if (!node)
			return (free(msg), error(proc, "msg_receive alloc"));
		lst_back(&proc->msg_list, node);
	}
}

/**
 * @brief send a message to client id, managing data parsing
 * 
 * @param proc {t_proc *} process data
 * @param id {int } id of the desired client (1=frontend)
 * @param msg_type {enum e_msg_event} see MSGE enum of messages 
 * @param data {void * | NULL} ptr with data to parse
 */
void	msg_sendId(t_proc *proc, int id, int msg_type, void *data)
{
	(void)data;
	if (id == proc->id)
		return ;
	proc->msg.mtype = id;
	proc->msg.buff[0] = msg_type;
	if (msg_type > 0 && msg_type < MSGE_NUM)
		MSG_PARSER[msg_type](proc, data);
	if (msgsnd(proc->msg_fd, &proc->msg, BUFF_LEN, IPC_NOWAIT) == -1)
		error(proc, "msgsnd failure");
	proc->msg.mtype = proc->id;
}

/**
 * @brief send a message to all clients, managing data parsing
 * 
 * @param proc {t_proc *} process data
 * @param msg_type {enum e_msg_event} see MSGE enum of messages 
 * @param data {void * | NULL} ptr with data to parse
 */
void	msg_sendAll(t_proc *proc, int msg_type, void *data)
{
	int	n_client;

	if (!proc->shared)
		return ;
	sem_wait(&proc->shared->sem);
	n_client = proc->shared->n_client;	
	sem_post(&proc->shared->sem);
	for (int i = 1; i != n_client; i++)
		msg_sendId(proc, i, msg_type, data);
}

static void	_parse_id(t_proc *proc, void *data)
{
	(void)data;
	ft_memcpy(proc->msg.buff + 1, &proc->id, sizeof(int));
}

static void	_parse_none(t_proc *proc, void *data)
{
	(void)proc, (void)data;
}
