/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   experiment.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 16:09:11 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/26 12:31:19 by alerusso         ###   ########.fr       */
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

# define BUFF_LEN 64
# define DEFAULT_NAME "default"
# define SHM_FILE "/lem-ipc_shared_memory"
# define SEM_FILE "/lem-ipc_sem"
# define MSQ_FILE "./"

typedef struct s_shared
{
	char	buff[BUFF_LEN];
	sem_t	sem;
	int		id;
	int		n_client;
}		t_shared;

typedef struct s_private
{
	long			msg_type;
	char			buff[BUFF_LEN];
	struct mq_attr	mq_info;	//mqueue info about queue
	t_shared		*shared_ptr;
	const char		*name;		//process name, from argv
	mqd_t			mq_fd;		//mqueue fd
	int				msg_fd;		//msg queue fd
	int				id;
	int				name_len;
	bool			master;		//true if shm file does not exist
}		t_private;

typedef struct s_msg
{
	long	mtype;
	char	buff[BUFF_LEN];	
}		t_msg;


void	setup(t_private *data, const char *name);
void	error(const char *err);
void	cleanup(t_shared *data);

#endif