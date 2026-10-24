/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 10:54:15 by alerusso42        #+#    #+#             */
/*   Updated: 2026/10/24 19:02:01 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "experiment.h"

static void	init(t_shared *shared);

void	setup(t_private *data, const char *name)
{
	int	fd;

	*data = (t_private){0};
	data->name = name ? name : DEFAULT_NAME;
	data->master = access("/dev/shm" SHM_FILE, F_OK) == -1;
	errno = 0;
	fd = shm_open(SHM_FILE, O_RDWR | O_CREAT, 0666);
	if (fd == -1)
		error("shm_open failed");
	data->shared_ptr = mmap(NULL, sizeof(t_shared), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (data == (void *)-1)
		return (close(fd), cleanup(data->shared_ptr), error("mmap failed"));
	if (ftruncate(fd, sizeof(t_shared)) != 0)
		return (close(fd), cleanup(data->shared_ptr), error("ftruncate failed"));
	close(fd);
	if (data->master == true)
		init(data->shared_ptr);
	sem_wait(&data->shared_ptr->sem);
	ft_printf("Number of active clients: %d\n", ++data->shared_ptr->n_client);
	sem_post(&data->shared_ptr->sem);
}

void	error(const char *err)
{
	perror(err);
	exit(1);
}

void	cleanup(t_shared *data)
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

static void	init(t_shared *shared)
{
	*shared = (t_shared){0};
	if (sem_init(&shared->sem, 1, 1) != 0)
		return (cleanup(shared), error("sem_init failed"));
	ft_printf("$Yshared memory created..$Z\n");
}
