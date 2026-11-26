/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 12:31:06 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/26 13:02:27 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
//SECTION - includes
#include "lem-ipc.h"

//SECTION - defines
#define GAME_SPEED 1e6f//micro seconds needed by a kart to go to a new coord

enum e_game
{
	INFO_TEAM_RED		= 0b00,
	INFO_TEAM_YELLOW	= 0b01,
	INFO_TEAM_GREEN		= 0b10,
	INFO_TEAM_BLUE	 	= 0b11,
	INFO_TEAM_NUM,
	INFO_PLAYER_END		= -1,//mark that player array is finished
	INFO_MAP_X			= 2,//map x = MAP_X * n_player
	INFO_MAP_Y			= 3,//map y = MAP_Y * n_player
	INFO_WALLMID_X		= 2,//
	INFO_WALLMID_Y		= 6,//
	INFO_SPRITE_SIZE	= 32,
	MOVE_NORTH			= 0,
	MOVE_EAST			= 1,
	MOVE_SOUTH			= 2,
	MOVE_WEST			= 3,
	MOVE_NUM,
	SQUARE_DENSITY		= 100,//square division to make fluid pixel transition
};

#define TEAMS_STR \
(const char *[])\
{\
	[INFO_TEAM_RED] 	= "RED",\
	[INFO_TEAM_YELLOW]	= "YELLOW",\
	[INFO_TEAM_GREEN]	= "GREEN",\
	[INFO_TEAM_BLUE]	= "BLUE",\
}

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

#define EMOJI_MAP \
(const char *[])\
{\
	[SQ_RED] 	= "🔴",\
	[SQ_YELLOW]	= "🟡",\
	[SQ_GREEN]	= "🟢",\
	[SQ_BLUE]	= "🔵",\
	[SQ_FREE]	= "  ",\
	[SQ_WALL]	= "🧱",\
	[SQ_NUM]	= NULL,\
}

typedef struct s_info
{
	uint8_t	num_team:3;
	uint8_t	team:2;
	uint8_t	move_dir:2;//see MOVE_* in enum e_game
	uint8_t	move_push:1;//true if player has been pushed
	uint8_t	move_stun:1;//true if player is stunned
	uint8_t	move_dead:1;//true if player is dead
	uint8_t	error:1;//on in case of error
	uint8_t	is_team_lock:1;
	uint8_t	is_ai:1;
	uint8_t	is_sdl_disabled:1;
	uint8_t	is_master:1;
	uint8_t	is_id_ok:1;
	uint8_t	is_offline:1;
}		t_info;

typedef struct s_player
{
	int		id;
	int		coord;
	float	edge_x;//goes from 0 to 31: represents pixels in x axis
	float	edge_y;//same for y axis
	t_info	info;
}		t_player;

//size = (sizeof(t_map) * (x_map * y_map))

typedef struct s_grid
{
	int			ids[INFO_TEAM_NUM];
	uint32_t	val;
}		t_grid;

typedef struct s_match
{
	int		team_offset[INFO_TEAM_NUM];//end of team array indexes
	float	move_chunk;
	int		player_num;//⚠️NEEDS s_gen sem. number of playing clients
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
