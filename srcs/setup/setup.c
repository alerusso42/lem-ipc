/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 15:13:11 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/05 09:21:04 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/setup.h"

static void	_shm_init(t_data *shared);

/**
 * @brief setups the shared memory
 * 
 * @param data ptr to data
 */
void	setup(t_data *data)
{
	int	fd;

	*data = (t_data){0};
	data->master = access("/dev/shm" SHM_FILE, F_OK) == -1;
	errno = 0;
	fd = shm_open(SHM_FILE, O_RDWR | O_CREAT, 0666);
	if (fd == -1)
		error(data, "shm_open failed");
	data->shared = mmap(NULL, sizeof(t_shared), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (data == (void *)-1)
		return (close(fd), error(data, "mmap failed"));
	if (ftruncate(fd, sizeof(t_shared)) != 0)
		return (close(fd), error(data, "ftruncate failed"));
	close(fd);
	if (data->master == true)
		_shm_init(data);
	sem_wait(&data->shared->sem);
	ft_printf("Number of active clients: %d\n", ++data->shared->n_client);
	data->id = ++data->shared->id_count;
	sem_post(&data->shared->sem);
}

static void	_shm_init(t_data *data)
{
	*data->shared = (t_shared){0};
	data->shared->id_count = 1;//id 1 is reserved for SDL3 frontend
	if (sem_init(&data->shared->sem, 1, 1) != 0)
		error(data, "sem_init failed");
	ft_printf("$Yshared memory created..$Z\n");
}
