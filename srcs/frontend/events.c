/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 18:29:15 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/16 17:54:55 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"

static void	_event_client_new(t_F *front, t_msg *msg);
static void	_event_client_del(t_F *front, t_msg *msg);
static void	_event_quit(t_F *front, t_msg *msg);
static void	_event_none(t_F *front, t_msg *msg);
// static int	_parse_id(t_msg *msg);

//https://stackoverflow.com/questions/252748/how-can-i-use-an-array-of-function-pointers
#define QUEUE_HANDLER \
(void (*[])(t_F *, t_msg*))\
{\
	[MSGE_INVALID] = _event_none,\
	[MSGE_CLIENT_NEW] = _event_client_new,\
	[MSGE_CLIENT_DEL] = _event_client_del,\
	[MSGE_QUIT] = _event_quit,\
	[MSGE_NUM] = _event_none\
}

void	F_events_queue(t_F *front)
{
	t_list	*next;
	t_msg	*msg;

	msg_receive(front->proc);
	while (front->proc->msg_list)
	{
		msg = front->proc->msg_list->content;
		if (msg && msg->buff[0] > 0 && msg->buff[0] < MSGE_NUM)
			QUEUE_HANDLER[(int)msg->buff[0]](front, msg);	
		next = front->proc->msg_list->next;
		lst_delone(front->proc->msg_list, free);
		front->proc->msg_list = next;
	}
}

//SECTION - handlers

static void	_event_client_new(t_F *front, t_msg *msg)
{
	(void)front;
	ft_printf("Welcome, client %d\n", msg->mtype);
}

static void	_event_client_del(t_F *front, t_msg *msg)
{
	bool	alone;

	ft_printf("Client %d left\n", msg->mtype);
	sem_wait(&front->proc->shared->sem);
	alone = front->proc->shared->n_client <= 1;	
	sem_post(&front->proc->shared->sem);
	if (alone)
		_event_quit(front, msg);
}

static void	_event_quit(t_F *front, t_msg *msg)
{
	(void)msg;
	front->power_on = false;
}

static void	_event_none(t_F *front, t_msg *msg)
{
	(void)front, (void)msg;
}

//SECTION - parse functions

// static int	_parse_id(t_msg *msg)
// {
// 	return (*(int *)(msg + 1));
// }
