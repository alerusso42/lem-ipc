/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_queue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 18:29:15 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/26 15:55:30 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"

static void	_event_client_new(t_F *front, t_msg *msg);
static void	_event_client_del(t_F *front, t_msg *msg);
static void	_event_quit(t_F *front, t_msg *msg);
static void	_event_start(t_F *front, t_msg *msg);
static void	_event_error(t_F *front, t_msg *msg);
static void	_event_none(t_F *front, t_msg *msg);
static int	_get_id(t_msg *msg);

//https://stackoverflow.com/questions/252748/how-can-i-use-an-array-of-function-pointers
#define QUEUE_HANDLER \
(void (*[])(t_F *, t_msg*))\
{\
	[MSGE_INVALID] = _event_none,\
	[MSGE_CLIENT_NEW] = _event_client_new,\
	[MSGE_CLIENT_DEL] = _event_client_del,\
	[MSGE_QUIT] = _event_quit,\
	[MSGE_START] = _event_start,\
	[MSGE_ERROR] = _event_error,\
	[MSGE_ID_ASK] = _event_none,\
	[MSGE_ID_RECEIVE] = _event_none,\
	[MSGE_NUM] = _event_none\
}

/**
 * @brief Listens and handles messages from backend
 * 
 * @param front 
 */
void	F_events_queue(t_F *front)
{
	t_msg	*msg;

	msg_receive(front->proc);
	while (front->proc->msg_list)
	{
		msg = front->proc->msg_list->content;
		if (msg && msg->buff[0] > 0 && msg->buff[0] < MSGE_NUM)
			QUEUE_HANDLER[(int)msg->buff[0]](front, msg);	
		lst_delone(&front->proc->msg_list, free);
	}
}

//SECTION - handlers

static void	_event_client_new(t_F *front, t_msg *msg)
{
	(void)front;
	debug_log_int(front->proc, "Welcome, client %d", _get_id(msg));
}

static void	_event_client_del(t_F *front, t_msg *msg)
{
	bool	alone;

	debug_log_int(front->proc, "Client %d left", _get_id(msg));
	sem_wait(&front->proc->shared->s_gen);
	alone = front->proc->shared->n_client <= 1;	
	sem_post(&front->proc->shared->s_gen);
	if (alone)
		_event_quit(front, msg);
}

static void	_event_quit(t_F *front, t_msg *msg)
{
	(void)msg;
	front->power_on = false;
}

static void	_event_start(t_F *front, t_msg *msg)
{
	(void)msg;
	F_modeGame(front);
	debug_log(front->proc, "start game ok");
	debug_drawMap(front->proc);
	debug_drawTeams(front->proc);
	for (int i = 0; i != MAX_SENTENCE; i++)
		F_txt_create(front, i, "WORKING IN PROGRESS!");
}

static void	_event_error(t_F *front, t_msg *msg)
{
	(void)front;
	debug_log_int_char(front->proc, "error from %d: \"%s\"", _get_id(msg), msg->buff + 1 + sizeof(int));
	F_txt_create(front, 4, msg->buff + 1 + sizeof(int));
}

static void	_event_none(t_F *front, t_msg *msg)
{
	(void)front, (void)msg;
	debug_log_int(front->proc, "Invalid message type from %d", _get_id(msg));
}

//SECTION - parse functions

static int	_get_id(t_msg *msg)
{
	return (*(int *)(msg->buff + 1));
}
