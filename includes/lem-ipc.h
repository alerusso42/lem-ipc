/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-ipc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 12:19:24 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/18 23:26:44 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
//SECTION - includes
#include "../Libft/libft.h"
#include "msg.h"
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
typedef struct s_info	t_info;
typedef struct s_player	t_player;
typedef struct s_square	t_square;
typedef struct s_match	t_match;

typedef struct s_info
{
	uint8_t	num_team:3;
	uint8_t	team:2;
	uint8_t	is_team_lock:1;
	uint8_t	is_ai:1;
	uint8_t	is_sdl_disabled:1;
	uint8_t	is_master:1;
	uint8_t	is_id_ok:1;
	uint8_t	error:1;//on in case of error
}		t_info;

typedef struct s_player
{
	int		id;
	t_info	info;
}		t_player;

typedef struct s_square
{
	int	square;
}		t_square;

typedef struct s_match
{
	uint8_t	is_start:1;
}		t_match;

typedef struct s_msg
{
	long	mtype;
	char	buff[BUFF_LEN];
}		t_msg;

enum e_info
{
	INFO_TEAM_RED		= 0b00,
	INFO_TEAM_YELLOW	= 0b01,
	INFO_TEAM_GREEN		= 0b10,
	INFO_TEAM_BLUE	 	= 0b11,
	INFO_TEAM_NUM,
};

enum e_default_settings
{
	DEFAULT_MATCHMAKING_TIMEOUT	= 42,//set if sdl=off
};

struct s_proc
{
	t_msg		msg;
	t_list		*msg_list;
	t_shared	*shared;	//shared data
	int			msg_fd;		//msg queue fd
	int			id;
	int			num_players;//minimum number of players to start
	t_info		info;
};

typedef struct s_shared
{
	t_match		match;
	sem_t		s_gen;//general semaphore
	sem_t		s_print;//print semaphore
	int			id_count;
	int			n_client;
	int			n_team;
	atomic_char	is_init;//https://beej.us/guide/bgc/html/split/chapter-atomics.html
	char 		heap[];
}		t_shared;

//SECTION - functions

void	parse_argv(t_proc *data, char **argv);
void	error(t_proc *data, const char *err);
void	cleanup(t_proc *data);
void	msg_receive(t_proc *data);
void	msg_sendId(t_proc *data, int id, int msg_type, void *ptr);
void	msg_sendAll(t_proc *data, int msg_type, void *ptr);
int		msg_get_id(t_msg *msg);
void	debug_log(t_proc *proc, const char *msg);
void	debug_log_int(t_proc *proc, const char *msg, int n);
void	debug_log_char(t_proc *proc, const char *msg, const char *s);
void	debug_log_char_char(t_proc *proc, const char *msg, const char *s1, const char *s2);
void	debug_log_int_int(t_proc *proc, const char *msg, int n1, int n2);
void	debug_log_int_char(t_proc *proc, const char *msg, int n, const char *s);