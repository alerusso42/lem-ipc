/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 12:53:13 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/27 10:27:32 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem-ipc.h"

static void	shm_cleanup(t_proc *data, t_shared *shared);
static void	_end_sem(t_shared *shared);

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
	shm_cleanup(data, data->shared);
	data->shared = NULL;
}

//shared resource cleanup
static void	shm_cleanup(t_proc *data, t_shared *shared)
{
	if (!shared || shared == (void *)-1)
		return ;
	if (data->info.is_master == true && shared->match.is_start == false)
		msg_sendAll(data, MSGE_QUIT, NULL);
	sem_wait(&shared->s_gen);
	if (shared->n_client == 2)
		msg_sendId(data, MSGID_FRONT, MSGE_QUIT, NULL);
	if (data->msg_fd > 0)
		close(data->msg_fd);
	if (shared->n_client == 1)
	{
		if (data->msg_fd < 0);
		else if (msgctl(data->msg_fd, IPC_RMID, NULL) != 0)
			perror("msgctl, IPC_RMID");
		else
			debug_log(data, "$YQueue completely DEMOLISHED.$Z");
		_end_sem(shared);
		shm_unlink(SHM_FILE);
		mq_unlink(MSQ_FILE);
		data->shared = NULL;
		debug_log(data, "$Yshared memory BRUTALLY DESTROYED.$Z");
	}
	else
	{
		shared->n_client -= 1;
		sem_post(&shared->s_gen);
	}
	debug_log(data, "exit after cleanup");
	munmap(shared, sizeof(t_shared));
}

static void	_end_sem(t_shared *shared)
{
	sem_destroy(&shared->s_player);
	sem_destroy(&shared->s_map);
	sem_destroy(&shared->s_print);
	sem_destroy(&shared->s_gen);
}
