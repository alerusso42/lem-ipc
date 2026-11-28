/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_management.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 17:12:15 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/28 13:10:04 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/backend.h"

/**
 * @brief [MASTER] - used when a new client arrives, to assign it a unique ID
 * 
 * A special array is used for the job. The array indexes correspond to IDs;
 * ID_FREE = free id; ID_TAKEN = occupied ID; ID_LAST = last array member.
 * @param back 
 * @param msg a message with a MSGE_ID_ASK type
 */
void	B_id_reserve(t_B *back, t_msg *msg)
{
	int	tmp_id;
	int	i;

	if (back->proc->info.is_master == false)
		return (debug_log(back->proc, "Client entered in B_id_reserve"));
	tmp_id = *(int *)(msg->buff + 1);
	if (!back->arr_id)
	{
		back->arr_id = ft_calloc(32, sizeof(uint8_t));
		if (!back->arr_id)
			B_error(back, "array of id cannot be created");
		back->arr_id[31] = ID_LAST;
	}
	for (i = MSGID_MASTER + 1; back->arr_id[i] != ID_FREE; i++)
	{
		if (back->arr_id[i] != ID_LAST)
			continue ;
		back->arr_id = realloc(back->arr_id, (i + 1) * 2);
		if (!back->arr_id)
			B_error(back, "array of id cannot be extended");
		back->arr_id[((i + 1) * 2) - 1] = ID_LAST;
		back->arr_id[i] = ID_FREE;
		break ;
	}
	back->arr_id[i] = ID_TAKEN;
	msg_sendId(back->proc, tmp_id, MSGE_ID_RECEIVE, &i);
}

/**
 * @brief [MASTER] - used when a client disconnects, to free its ID.
 * 
 * The enum ID_FREE is used to mark its ID as free in the array.
 * 
 * @param back 
 * @param msg a message with a MSGE_CLIENT_DEL type
 */
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

/**
 * @brief [CLIENT] - Used by clients to receive a unique ID.
 * 		
 * a message with a temponary ID is sent to the master, then the client
 * awaits to receive a message of type MSGE_ID_RECEIVE.
 * In case of success, notifies everyone that a new client arrived; else, exits.
 * 
 * @param back 
 * @param msg a message with a MSGE_CLIENT_DEL type
 */
void	B_id_wait(t_B *back)
{
	t_msg	*msg;

	if (back->proc->info.is_master == true)
		return (debug_log(back->proc, "Master entered in B_id_wait"));
	msg_sendId(back->proc, MSGID_MASTER, MSGE_ID_ASK, NULL);
	timer_reset(&back->timers[TIMB_ID_WAIT]);
	while (back->power_on == true)
	{
		msg_receive(back->proc);
		while (back->proc->msg_list)
		{
			msg = back->proc->msg_list->content;
			if (*msg->buff == MSGE_ID_RECEIVE)
			{
				back->timers[TIMB_ID_WAIT].freeze = true;
				back->proc->id = *(int *)(msg->buff + 1);
				back->proc->info.is_id_ok = true;
				msg_sendAll(back->proc, MSGE_CLIENT_NEW, NULL);
				lst_clear(&back->proc->msg_list, free);
				debug_log(back->proc, "id received.");
				return ;
			}
			lst_delone(&back->proc->msg_list, free);
		}
		timer_check(&back->timers[TIMB_ID_WAIT]);//quit when expires
	}
	B_error(back, "new id did not arrive in time :-(");
}

/**
 * @brief [CLIENT] - Used by clients to search their player ID.
 * 		
 * The ID is searched in t_player array from the t_shared's heap.
 * 
 * @param back 
 */
void	B_id_player(t_B *back)
{
	int	start_team;
	int	end_team;

	start_team = back->match->team_offset[back->proc->info.team];
	end_team = back->match->team_offset[back->proc->info.team + 1];
	for (int i = start_team; i < end_team; i++)
	{
		if (back->players[i].id != back->proc->id)
			continue ;
		back->id_player = back->players[i].id;
		return ;
	}
	B_error(back, "My player id is missing");
}
