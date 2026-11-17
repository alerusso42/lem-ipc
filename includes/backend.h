/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 12:22:05 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/17 20:30:52 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
//SECTION - includes
#include "lem-ipc.h"
#include <signal.h>
//SECTION - defines

//SECTION - data structures

typedef struct s_backend		t_B;
typedef struct s_matchmaking	t_MatchMaking;

struct s_matchmaking
{
	int		teams_size[INFO_TEAM_NUM];
	t_list	*players;//t_player list
	int		size;
	bool	start;
};

struct s_backend
{
	t_proc		*proc;//process data
	bool		power_on;
};

//SECTION - functions

void	B_matchmaking(t_B *back);