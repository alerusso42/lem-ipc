/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_mutex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 18:36:50 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/14 15:06:56 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"

/**
 * F_mutex critical section: 
 * @brief this function calls other non thread-safe functions, 
 * 		managing lock/unlock.
 * 
 * @param front 
 * @param f size_t	(t_F *front);	//may return 0
 * @return size_t a copy of the data (default: zero) 
 */
size_t	F_mutexCs(t_F *front, size_t (*f)(t_F *))
{
	size_t	copy;

	SDL_LockMutex(front->sdl.mutex);
	copy = f(front);
	SDL_UnlockMutex(front->sdl.mutex);
	return (copy);
}

/**
 * @brief THREAD UNSAFE: checks frontend run status
 * 
 * @param front 
 * @return size_t returns current power_on boolean value
 */
size_t	F_mutex_runCheck(t_F *front)
{
	return (front->power_on);	
}

/**
 * @brief THREAD UNSAFE: shuts down frontend
 * 
 * @param front 
 * @return size_t unused
 */
size_t	F_mutex_runStop(t_F *front)
{
	front->power_on = false;
	return (0);	
}

/**
 * @brief THREAD UNSAFE: get next message in the msg queue
 * 
 * @param front 
 * @return size_t next msg ptr
 */
size_t	F_mutex_getNextMsg(t_F *front)
{
	if (front->msg_parsed != NULL)
		return ((size_t)front->msg_parsed->next);
	front->msg_parsed = front->msg_list;
	return ((size_t)front->msg_list);
}

/**
 * @brief THREAD UNSAFE: delete current message in the msg queue
 * 		if no msg are left, the list is set as NULL
 * @param front 
 * @return size_t unused
 */
size_t	F_mutex_delCurrMsg(t_F *front)
{
	bool	last;

	if (front->msg_parsed == NULL)
		return (0);
	front->msg_parsed = front->msg_parsed->next;
	last = front->msg_parsed == NULL;
	lst_delone(front->msg_list, free);
	if (last == true)
	{
		front->msg_list = NULL;
		front->msg_last = NULL;
		front->msg_parsed = NULL;
	}
	return (0);
}

/**
 * @brief THREAD UNSAFE: add message in the msg queue
 * @note RESERVED TO queue handler thread 
 * 
 * @param front 
 * @return size_t next msg ptr
 */
size_t	F_mutex_addMsg(t_F *front)
{
	t_msg	*msg;
	t_list	*node;

	msg = malloc(sizeof(t_msg));
	if (!msg)
		return (F_mutex_runStop(front));
	node = lst_new(msg);
	if (!node)
		return (free(msg), F_mutex_runStop(front));
	ft_memcpy(msg, &front->msg, sizeof(t_msg));
	lst_front(&front->msg_last, node);
	if (!front->msg_list)
		front->msg_list = front->msg_last;
	return (0);
}
