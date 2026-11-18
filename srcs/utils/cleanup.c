/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 12:53:13 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/18 19:37:24 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem-ipc.h"

static void	_shm_cleanup(t_proc *data, t_shared *shared);

/**
 * @brief used when a kernel/library function fails
 * 
 * @param data ptr to program data
 * @param err the message error
 */
void	error(t_proc *data, const char *err)
{
	data->info.error = true;
	if (err && errno)
		perror(err);
	else if (err)
		debug_log(data, err);
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
	data->shared = NULL;
	debug_log(data, "exit after cleanup");
}

//shared resource cleanup
static void	_shm_cleanup(t_proc *data, t_shared *shared)
{
	if (!shared || shared == (void *)-1)
		return ;
	if (data->info.is_master == true && shared->match.is_start == false)
		msg_sendAll(data, MSGE_QUIT, NULL);
	sem_wait(&shared->s_gen);
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
			debug_log(data, "$YQueue completely DEMOLISHED.$Z");
		sem_close(&shared->s_gen);
		sem_destroy(&shared->s_gen);
		sem_close(&shared->s_print);
		sem_destroy(&shared->s_print);
		shm_unlink(SHM_FILE);
		mq_unlink(MSQ_FILE);
		debug_log(data, "$Yshared memory BRUTALLY DESTROYED.$Z");
	}
	else
	{
		shared->n_client -= 1;
		sem_post(&shared->s_gen);
		sem_close(&shared->s_gen);
		sem_close(&shared->s_print);
	}
	munmap(shared, sizeof(t_shared));
}
