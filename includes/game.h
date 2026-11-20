/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 12:31:06 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/20 12:07:01 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
//SECTION - includes
#include "lem-ipc.h"

typedef struct s_player	t_player;
typedef struct s_grid	t_grid;
typedef struct s_match	t_match;
typedef struct s_info	t_info;

typedef struct s_info
{
	uint8_t	num_team:3;
	uint8_t	team:2;
	uint8_t	is_team_lock:1;
	uint8_t	is_ai:1;
	uint8_t	is_sdl_disabled:1;
	uint8_t	is_master:1;
	uint8_t	is_id_ok:1;
	uint8_t	is_offline:1;
	uint8_t	error:1;//on in case of error
}		t_info;

typedef struct s_player
{
	int		id;
	t_info	info;
}		t_player;

//size = (sizeof(t_map) * (x_map * y_map))

typedef struct s_grid
{
	int		id;
	uint8_t	val;
}		t_grid;

// //opzione 1
// //   80056UL	20	
// //  640056UL	40
// //10000056UL	100
// //opzione 2
// //    80056UL	20	
// //   640056UL	40
// //  5600000UL	100
// //560000000UL	1000
// #define	n_client 6
// #define	x_map n_client * 1
// #define	y_map n_client * 3
// int size = (sizeof(t_map) * (x_map * y_map));

typedef struct s_match
{
	int		map_x;
	int		map_y;
	int		map_area;
	int		map_topr;//top right
	int		map_topl;//top left
	int		map_botr;//bottom right
	int		map_botl;//bottom left
	int		wall_bot_r;//mid wall bottom coordinate
	int		wall_top_r;//mid wall top coordinate
	int		wall_bot_l;//mid wall left bottom coordinate (only with even grid)
	int		wall_top_l;//mid wall left top coordinate (only with even grid)
	int		wall_offx_r;//wall offset on x axis
	int		wall_offy_r;//wall offset on y axis
	int		wall_offx_l;//left wall offset on x axis (only with even grid)
	int		wall_offy_l;//left wall offset on y axis (only with even grid)
	uint8_t	is_start:1;
}		t_match;

enum e_game
{
	INFO_TEAM_RED		= 0b00,
	INFO_TEAM_YELLOW	= 0b01,
	INFO_TEAM_GREEN		= 0b10,
	INFO_TEAM_BLUE	 	= 0b11,
	INFO_TEAM_NUM,
	INFO_MAP_X			= 2,//map x = MAP_X * n_player
	INFO_MAP_Y			= 3,//map y = MAP_Y * n_player
	INFO_WALLMID_X		= 2,//
	INFO_WALLMID_Y		= 6,//
};

enum e_default_settings
{
	DEFAULT_MATCHMAKING_TIMEOUT	= 42,//set if sdl=off
};

enum e_squares
{
	SQ_RED = INFO_TEAM_RED,	
	SQ_YELLOW = INFO_TEAM_YELLOW,
	SQ_GREEN = INFO_TEAM_GREEN,
	SQ_BLUE = INFO_TEAM_BLUE,
	SQ_FREE,
	SQ_WALL,
	SQ_NUM
};