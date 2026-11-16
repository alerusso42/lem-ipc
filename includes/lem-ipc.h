/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-ipc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 12:19:24 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/16 17:46:37 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
//SECTION - includes
#include "../Libft/libft.h"
#include "msg.h"
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

typedef struct s_proc
{
	t_msg		msg;
	t_list		*msg_list;
	t_shared	*shared;	//shared data
	int			msg_fd;		//msg queue fd
	int			id;
	bool		master;		//true if shm file does not exist
}		t_proc;

//SECTION - functions

void	error(t_proc *data, const char *err);
void	cleanup(t_proc *data);
void	msg_receive(t_proc *data);
void	msg_sendId(t_proc *data, int id, int msg_type, void *ptr);
void	msg_sendAll(t_proc *data, int msg_type, void *ptr);