/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 15:13:11 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/18 19:07:24 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem-ipc.h"

static void	_shm_init(t_proc *shared);
static void	_msgq_init(t_proc *data);

/**
 * @brief setups the shared memory
 * 
 * @param data ptr to data
 */
void	setup(t_proc *data, char **argv)
{
	int	fd;
	int	n_client;
	int	n_team;

	*data = (t_proc){0};
	data->msg_fd = -1;
	parse_argv(data, argv);
	//NOTE - if two processes becomes master, _shm_init handles it
	data->info.is_master = access("/dev/shm" SHM_FILE, F_OK) == -1;
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
	if (data->info.is_master == true)
		_shm_init(data);
	_msgq_init(data);
	sem_wait(&data->shared->s_gen);
	if (data->info.is_master == false && data->shared->match.is_start == true)
		return (sem_post(&data->shared->s_gen), error(data, "Match is started"));
	n_client = ++data->shared->n_client;
	data->id = data->shared->id_count;
	n_team = data->shared->n_team;
	sem_post(&data->shared->s_gen);
	debug_log_int(data, "Number of active clients: %d", n_client);
	if (data->info.is_master == false && data->info.team >= n_team + 1)
		error(data, "in the choosen number of teams, your color does not exist.");
	else if (data->info.is_master == true)
		data->shared->id_count += 1;
}

/**
 * @brief initialize shared memory and semaphore, if does not exist yet.\
 * 
 * an atomic variable checks that two masters cannot exist
 * 
 * @param data 
 */
static void	_shm_init(t_proc *data)
{
	char	is_init;

	is_init = ++data->shared->is_init;
	if (is_init != 1)
	{
		munmap(data->shared, sizeof(data->shared));
		shm_unlink(SHM_FILE);
		err_printf("two master detected.\n");
		exit(1);
	}
	if (sem_init(&data->shared->s_gen, 1, 1) != 0)
		error(data, "sem_init failed");
	if (sem_init(&data->shared->s_print, 1, 1) != 0)
		error(data, "sem_init failed");
	data->shared->id_count = 2;//id 1 is reserved for SDL3 frontend
	data->shared->n_team = data->info.num_team;
	data->info.is_id_ok = true;
	debug_log(data, "$Yshared memory created..$Z");
}

//	usage of msgget taken from here
//https://stackoverflow.com/questions/49570961/message-queue-msgget-msgsnd-msgrcv-linux-eidrm
//https://stackoverflow.com/questions/7358400/whats-is-purpose-ftok-in-message-queues
static void	_msgq_init(t_proc *data)
{
	key_t			key;

	key = ftok(MSQ_FILE, 42);
	if (key < 0)
		return (error(data, "ftok"));
	data->msg_fd = msgget(key, IPC_CREAT | 0666);
	if (data->msg_fd < 0)
		return (error(data, "msgget"));
}
