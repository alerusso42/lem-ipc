/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 12:22:05 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/27 02:40:31 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
//SECTION - includes
#include "lem-ipc.h"
#include <signal.h>
//SECTION - defines

//SECTION - timers

enum e_b_timer
{
	TIMB_ID_WAIT,//time clients wait to receive their ID
	TIMB_MATCHMAKING,//use to test stuff
	TIMB_BFS,//triggers bfs search
	TIMB_MOVE,//triggers movement
	TIMB_MOVE_PUSH,//timeout for movement push
	TIMB_MOVE_STUN,//timeout for stun effect
	TIMB_TEST,//use to test stuff
	TIMB_NUM
};

//SECTION - data structures

typedef struct s_backend		t_B;
typedef struct s_matchmaking	t_matchmaking;

extern volatile int	global_sigint;

struct s_matchmaking
{
	int		teams_size[INFO_TEAM_NUM];
	t_list	*players;//t_player list
	int		size;
	bool	start;
};

struct s_backend
{
	t_timer		timers[TIMB_NUM];//used to manage time events
	t_grid		*map_copy;//frontend game map
	t_match		*match;//ptr to shared memory
	t_grid		*map;//⚠️NEEDS s_map sem. ptr to shared memory
	t_player	*players;//⚠️NEEDS s_player sem. ptr to shared memory
	t_list		*players_start_info;
	t_proc		*proc;//process data
	uint8_t		*arr_id;
	uint8_t		power_on:1;
	uint8_t		timeout_matchmaking:1;
};

enum e_backend
{
	ID_FREE = 0,	
	ID_TAKEN = 1,	
	ID_LAST = 2,
	DEFAULT_WAIT = 500000
};

//SECTION - functions

void	B_sigint(int sig);
void	B_stop(t_B *backend);
void	B_error(t_B *backend, const char *err);
void	B_timer_start(t_B *back);
void	B_id_reserve(t_B *back, t_msg *msg);
void	B_id_release(t_B *back, t_msg *msg);
void	B_id_wait(t_B *back);
void	B_matchmaking(t_B *back);
void	B_setup_game(t_B *back);