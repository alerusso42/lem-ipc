/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-ipc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 12:19:24 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/03 15:32:52 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
//SECTION - includes
#include "../Libft/libft.h"
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <semaphore.h>
//SECTION - defines
#define SHM_FILE "/lem-ipc_shared_memory"
#define SEM_FILE "/lem-ipc_sem"
#define MSQ_FILE "./"
#define BUFF_LEN 64
//SECTION - data structures
typedef struct s_shared
{
	sem_t	sem;
	int		id_count;
	int		n_client;
}		t_shared;

typedef struct s_msg
{
	long	mtype;
	char	buff[BUFF_LEN];	
}		t_msg;

typedef struct t_data
{
	t_msg		msg;
	t_shared	*shared;
	int			msg_fd;		//msg queue fd
	int			id;
	bool		master;		//true if shm file does not exist
}		t_data;

//SECTION - functions

void	error(t_data *data, const char *err);
void	cleanup(t_data *data);