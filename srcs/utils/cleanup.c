/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 12:53:13 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/17 12:28:43 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/backend.h"

static void	_shm_cleanup(t_proc *data, t_shared *shared);

/**
 * @brief used when a kernel/library function fails
 * 
 * @param data ptr to program data
 * @param err the message error
 */
void	error(t_proc *data, const char *err)
{
	perror(err);
	cleanup(data);
	exit(1);
}

/**
 * @brief Safely cleanup data. 
 * If the process is the last to quit:
 * 	-	shm is cleaned
 * 	-	message queue in deleted
 * 	-	semaphore is destroyed
 * 
 * @param data ptr to program data
 */
void	cleanup(t_proc *data)
{
	if (!data)
		return ;
	lst_clear(&data->msg_list, free);
	msg_sendAll(data, MSGE_CLIENT_DEL, NULL);
	_shm_cleanup(data, data->shared);
}

//shared resource cleanup
static void	_shm_cleanup(t_proc *data, t_shared *shared)
{
	if (!shared || shared == (void *)-1)
		return ;
	sem_wait(&shared->sem);
	if (shared->n_client == 2)
		msg_sendId(data, 1, MSGE_QUIT, NULL);
	if (data->msg_fd > 0)
		close(data->msg_fd);
	if (shared->n_client == 1)
	{
		if (data->msg_fd < 0);
		else if (msgctl(data->msg_fd, IPC_RMID, NULL) != 0)
			perror("msgctl, IPC_RMID");
		else
			ft_printf("$YQueue completely DEMOLISHED.\n$Z");
		sem_close(&shared->sem);
		sem_destroy(&shared->sem);
		shm_unlink(SHM_FILE);
		mq_unlink(MSQ_FILE);
		ft_printf("$Yshared memory BRUTALLY DESTROYED.$Z\n");
	}
	else
	{
		shared->n_client -= 1;
		sem_post(&shared->sem);
		sem_close(&shared->sem);
	}
	munmap(shared, sizeof(t_shared));
}
