/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_msg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 10:49:41 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/27 11:08:38 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/backend.h"

static void	_event_client_del(t_B *back, t_msg *msg);
static void	_event_client_quit(t_B *back, t_msg *msg);

#define EVENTS_HANDLER \
(void (*[])(t_B*, t_msg*))\
{\
	[MSGE_INVALID] = NULL,\
	[MSGE_CLIENT_NEW] = NULL,\
	[MSGE_CLIENT_DEL] = _event_client_del,\
	[MSGE_QUIT] = _event_client_quit,\
	[MSGE_START] = NULL,\
	[MSGE_ID_ASK] = NULL,\
	[MSGE_ID_RECEIVE] = NULL,\
	[MSGE_NUM] = NULL\
}

void	B_game_msg(t_B *back)
{
	t_msg	*msg;
	int		msge;

	msg_receive(back->proc);
	while (back->proc->msg_list)
	{
		msg = back->proc->msg_list->content;
		msge = msg ? (int)*(msg->buff) : -1;
		if (msge >= 0 && msge < MSGE_NUM && EVENTS_HANDLER[msge])
			EVENTS_HANDLER[msge](back, msg);
		lst_delone(&back->proc->msg_list, free);
	}
}

static void	_event_client_del(t_B *back, t_msg *msg)
{
	debug_log_int(back->proc, "client %d left", *(int *)(msg->buff + 1));
}

static void	_event_client_quit(t_B *back, t_msg *msg)
{
	(void)msg;
	debug_log(back->proc, "Request quit..");
	back->power_on = false;
}
