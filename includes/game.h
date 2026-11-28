/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 12:31:06 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/28 15:33:50 by alerusso42       ###   ########.fr       */
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
	INFO_PLAYER_NONE	= -1,//mark that player array is finished
	INFO_MAP_X			= 1,//map x = MAP_X * n_player
	INFO_MAP_Y			= 1,//map y = MAP_Y * n_player
	INFO_WALLMID_X		= 2,//
	INFO_WALLMID_Y		= 6,//
	INFO_SPRITE_SIZE	= 32,
	MOVE_NORTH			= 1 << 0,
	MOVE_EAST			= 1 << 1,
	MOVE_SOUTH			= 1 << 2,
	MOVE_WEST			= 1 << 3,
	MOVE_Y				= MOVE_NORTH | MOVE_SOUTH,
	MOVE_X				= MOVE_WEST | MOVE_EAST,
	MOVE_REVERSE		= MOVE_NORTH | MOVE_WEST,//decrements x/y
	SQUARE_DELETE		= 4,//used to mark squares to delete from player
	SQUARE_DENSITY		= 100,//square division to make fluid pixel transition
	KART_MAX_SQUARE		= 4,
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
	uint8_t	move_dir:4;//see MOVE_* in enum e_game
	uint8_t	move_push:1;//true if player has been pushed
	uint8_t	move_stun:1;//true if player is stunned
	uint8_t	move_dead:1;//true if player is dead
	uint8_t	move_stop:1;//true if player is not moving
	uint8_t	move_run:1;//if false, accelerating to a wall will not cause stun
	uint8_t	error:1;//on in case of error
	uint8_t	is_team_lock:1;
	uint8_t	is_ai:1;
	uint8_t	is_sdl_disabled:1;
	uint8_t	is_master:1;
	uint8_t	is_id_ok:1;
	uint8_t	is_offline:1;
}		t_info;

typedef struct s_coord
{
	int32_t	x;
	int32_t	y;
}		t_coord;

typedef struct s_fcoord
{
	float	x;
	float	y;
}		t_fcoord;

typedef struct s_player
{
	int			map_id[KART_MAX_SQUARE];//kart can be in maximum 4 squares
	int			id;
	t_fcoord	edge;//goes from 0 to TEXTURE_SIZE: represents pixels
	t_info		info;
}		t_player;

//size = (sizeof(t_map) * (x_map * y_map))

typedef struct s_grid
{
	int			ids[KART_MAX_SQUARE];//squares can have maximum 4 karts
	uint32_t	val;
}		t_grid;

typedef struct s_match
{
	int		team_offset[INFO_TEAM_NUM + 1];//start of team array indexes
	t_coord	wall_off_r;//right wall offset
	t_coord	wall_off_l;//left wall offset (only with even grid)
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
	uint8_t	is_start:1;
}		t_match;
