/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 12:53:13 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/03 15:10:46 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/setup.h"

static void	_shm_cleanup(t_shared *data, int msg_fd);

/**
 * @brief used when a kernel/library function fails
 * 
 * @param data ptr to program data
 * @param err the message error
 */
void	error(t_data *data, const char *err)
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
 * @param data 
 */
void	cleanup(t_data *data)
{
	_shm_cleanup(data->shared, data->msg_fd);
}

//shared resource cleanup
static void	_shm_cleanup(t_shared *data, int msg_fd)
{
	if (!data || data == (void *)-1)
		return ;
	sem_wait(&data->sem);
	if (data->n_client == 1)
	{
		if (!msg_fd);
		else if (msgctl(msg_fd, IPC_RMID, NULL) != 0)
			perror("msgctl, IPC_RMID");
		else
			ft_printf("$Y Queue completely DEMOLISHED.\n$Z");
		sem_close(&data->sem);
		sem_destroy(&data->sem);
		shm_unlink(SHM_FILE);
		mq_unlink(MSQ_FILE);
		ft_printf("$Yshared memory BRUTALLY DESTROYED.$Z\n");
	}
	else
	{
		data->n_client -= 1;
		sem_post(&data->sem);
		sem_close(&data->sem);
	}
	munmap(data, sizeof(t_shared));
}
