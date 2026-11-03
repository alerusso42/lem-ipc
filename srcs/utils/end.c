/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 12:53:13 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/03 13:00:14 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/setup.h"

static void	_shm_cleanup(t_shared *data);

void	error(t_data *data, const char *err)
{
	perror(err);
	cleanup(data);
	exit(1);
}

void	cleanup(t_data *data)
{
	_shm_cleanup(data->shared);
}

static void	_shm_cleanup(t_shared *data)
{
	if (!data || data == (void *)-1)
		return ;
	sem_wait(&data->sem);
	if (data->n_client == 1)
	{
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
