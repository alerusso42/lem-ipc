/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   experiment.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 16:09:11 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/24 11:54:24 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPERIMENT_H
# define EXPERIMENT_H
# include "../../Libft/libft.h"
# include <sys/mman.h>
# include <sys/msg.h>
# include <sys/time.h>
# include <semaphore.h>
# include <mqueue.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>
# include <sys/msg.h>

# define BUFF_LEN 64
# define DEFAULT_NAME "default"
# define SHM_FILE "/lem-ipc_shared_memory"
# define SEM_FILE "/lem-ipc_sem"
# define MSQ_FILE "/lem-ipc_msgq_g"

typedef struct s_shared
{
	char	buff[BUFF_LEN];
	sem_t	sem;
	int		id;
	int		n_client;
}		t_shared;

typedef struct s_private
{
	char			buff[BUFF_LEN];
	struct mq_attr	mq_info;
	t_shared		*shared_ptr;
	const char		*name;
	mqd_t			mq_fd;
	bool			master;
}		t_private;

void	setup(t_private *data, const char *name);
void	error(const char *err);
void	cleanup(t_shared *data);

#endif