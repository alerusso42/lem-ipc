/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-ipc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 12:19:24 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/20 12:12:44 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
//SECTION - includes
#include "../Libft/libft.h"
#include "msg.h"
#include "game.h"
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <semaphore.h>
#include <mqueue.h>
#include <sys/mman.h>
#include <sys/msg.h>
#include <sys/time.h>
#include <fcntl.h>
//SECTION - defines
#define SHM_FILE "/lem-ipc_shared_memory"
#define SEM_FILE "/lem-ipc_sem"
#define MSQ_FILE "./"
#define BUFF_LEN 64
//SECTION - data structures

typedef struct s_proc	t_proc;
typedef struct s_shared	t_shared;
typedef struct s_msg	t_msg;

typedef struct s_msg
{
	long	mtype;
	char	buff[BUFF_LEN];
}		t_msg;

struct s_proc
{
	t_msg		msg;
	t_list		*msg_list;
	t_shared	*shared;//shared data
	t_grid		*map;//⚠️NEEDS s_map sem
	t_player	*players;//⚠️NEEDS s_player sem
	int			msg_fd;//msg queue fd
	int			id;
	int			num_players;//minimum number of players to start
	t_info		info;
};

typedef struct s_shared
{
	t_match		match;//⚠️NEEDS s_gen sem
	sem_t		s_gen;//general semaphore
	sem_t		s_print;//print semaphore
	sem_t		s_map;//map semaphore
	sem_t		s_player;//player semaphore
	size_t		shm_size;//[MASTER ONLY] - size in bytes of shared memory
	size_t		offset_player;//offset from which the player array starts
	int			id_count;//[MASTER ONLY] - a counter used to give temp IDs
	int			n_client;//⚠️NEEDS s_gen sem
	int			n_team;//number of teams
	atomic_char	is_init;//https://beej.us/guide/bgc/html/split/chapter-atomics.html
	char 		heap[];//buffer that stores {game map, player data array}
}		t_shared;

//SECTION - functions

void	parse_argv(t_proc *data, char **argv);
void	error(t_proc *data, const char *err);
void	cleanup(t_proc *data);
void	shm_cleanup(t_proc *data, t_shared *shared, bool copy);
bool	shm_extend(t_proc *data, size_t size);
bool	shm_update(t_proc *data);
void	cr_lockAll(t_proc *proc);
void	cr_unlockAll(t_proc *proc);
void	msg_receive(t_proc *data);
void	msg_sendId(t_proc *data, int id, int msg_type, void *ptr);
void	msg_sendAll(t_proc *data, int msg_type, void *ptr);
int		msg_get_id(t_msg *msg);
bool	grid_issquare_wall(t_proc *proc, int coord);
void	debug_log(t_proc *proc, const char *msg);
void	debug_drawMap(t_proc *proc);
void	debug_log_int(t_proc *proc, const char *msg, int n);
void	debug_log_char(t_proc *proc, const char *msg, const char *s);
void	debug_log_char_char(t_proc *proc, const char *msg, const char *s1, const char *s2);
void	debug_log_int_int(t_proc *proc, const char *msg, int n1, int n2);
void	debug_log_int_char(t_proc *proc, const char *msg, int n, const char *s);