/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_management.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 17:12:15 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/18 19:06:39 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/backend.h"

static void	_update_id_counter(t_B *back);

void	B_id_reserve(t_B *back, t_msg *msg)
{
	int	tmp_id;
	int	i;

	if (back->proc->info.is_master == false)
		return (debug_log(back->proc, "Client entered in B_id_reserve"));
	tmp_id = *(int *)(msg->buff + 1);
	if (!back->arr_id)
	{
		back->arr_id = ft_calloc(32, 1);
		if (!back->arr_id)
			B_error(back, "array of id cannot be created");
		back->arr_id[31] = ID_LAST;
	}
	for (i = MSGID_MASTER + 1; back->arr_id[i] != ID_FREE; i++)
	{
		if (back->arr_id[i] == ID_LAST)
		{
			back->arr_id = realloc(back->arr_id, i * 2);
			if (!back->arr_id)
				B_error(back, "array of id cannot be extended");
			back->arr_id[(i * 2) - 1] = ID_LAST;
			back->arr_id[i] = ID_FREE;
		}
	}
	back->arr_id[i] = ID_TAKEN;
	msg_sendId(back->proc, tmp_id, MSGE_ID_RECEIVE, &i);
	_update_id_counter(back);
}

void	B_id_release(t_B *back, t_msg *msg)
{
	int	i;

	if (back->proc->info.is_master == false)
		return (debug_log(back->proc, "Client entered in B_id_reserve"));
	i = *(int *)(msg->buff + 1);
	if (!back->arr_id || i == MSGID_FRONT)
		return ;
	back->arr_id[i] = ID_FREE;
}

void	B_id_wait(t_B *back)
{
	t_msg	*msg;
	int		tries;

	if (back->proc->info.is_master == true)
		return (debug_log(back->proc, "Master entered in B_id_wait"));
	msg_sendId(back->proc, MSGID_MASTER, MSGE_ID_ASK, NULL);
	tries = DEFAULT_ID_TRIES;
	while (tries--)
	{
		msg_receive(back->proc);
		while (back->proc->msg_list)
		{
			msg = back->proc->msg_list->content;
			if (*msg->buff == MSGE_ID_RECEIVE)
			{
				back->proc->id = *(int *)(msg->buff + 1);
				back->proc->info.is_id_ok = true;
				msg_sendAll(back->proc, MSGE_CLIENT_NEW, NULL);
				lst_clear(&back->proc->msg_list, free);
				return ;
			}
			lst_delone(&back->proc->msg_list, free);
		}
		usleep(DEFAULT_WAIT);
	}
	lst_clear(&back->proc->msg_list, free);
	B_error(back, "new id did not arrive in time :-(");
}

static void	_update_id_counter(t_B *back)
{
	back->proc->shared->id_count += 1;
	if (back->proc->shared->id_count == INT_MIN)
	{
		sem_wait(&back->proc->shared->s_gen);
		back->proc->shared->id_count = back->proc->shared->n_client + 1;
		sem_post(&back->proc->shared->s_gen);
	}
}
