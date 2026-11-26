/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frontend.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:16:42 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/26 15:50:57 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
//SECTION - includes
#include "lem-ipc.h"
#include "media.h"
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
# include <sys/msg.h>

//SECTION - defines
#define WINDOW_WIDTH	1920
#define WINDOW_HEIGTH	1080
#define FPS				(double)60
#define FRAME_TIME		(int)((1000000.0 / FPS) + 0.5)
#define MAX_SENTENCE	5//maximum number of text in screen
//16 - 9 = 7(delay)
//SECTION - data structures

/**
 * @brief frontend main structure.
 * @param {t_sdl}		sdl data
 * @param {t_msg}		message queue buffer
 * @param {t_shared *}	shared memory ptr
 * @param {int}			message queue fd
 * 
 */
typedef struct s_frontend	t_F;

typedef struct s_sdl		t_sdl;
typedef struct s_textures	t_textures;
typedef struct s_sounds		t_sounds;
typedef struct s_fonts		t_fonts;
typedef struct s_sentence	t_sentence;

struct s_textures
{
	SDL_Texture	*ptr;
};

struct s_sounds
{
	MIX_Audio	*ptr;
};

struct s_fonts
{
	TTF_Font	*ptr;	
};

struct s_sentence
{
	SDL_Texture	*ptr;
	char		*text;
	SDL_FRect	coords;
	int			timeout;
};

typedef struct s_info_F
{
	uint8_t	is_paused:1;//true if the pause is on
	uint8_t	is_playing:1;//1=game mode; 0=title mode
}		t_info_F;

enum e_timer
{
	TIM_FPS,//used to delay frames
	TIM_SECOND,//used to handle 1 second events
	TIM_END,//test if no other clients are connected
	TIM_RENDER,//delay the render
	TIM_TEST,//use to test stuff
	TIM_NUM
};

struct s_sdl
{
	t_textures		txt[TXT_NUM];
	t_sounds		sounds[SOUND_MUSIC_NUM];
	t_fonts			fonts[FONTS_NUM];
	t_sentence		sentence[MAX_SENTENCE];
	SDL_Event		event;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	MIX_Mixer		*mixer;
	MIX_Track		*track;
	TTF_TextEngine	*text_engine;
	TTF_Font		*text_font;
	int				win_x;
	int				win_y;
};

struct s_frontend
{
	t_sdl		sdl;
	t_timer		timers[TIM_NUM];//used to manage time events
	t_grid		*map_copy;//frontend game map
	t_player	*players_copy;//frontend game map
	t_match		*match;//ptr to shared memory
	t_grid		*map;//⚠️NEEDS s_map sem. ptr to shared memory
	t_player	*players;//⚠️NEEDS s_player sem. ptr to shared memory
	t_proc		*proc;//process data
	int			fps;
	int			fps_count;//counter used to count frames; reset by TIM_SECOND
	t_info_F	info;		
	bool		power_on;
};

//SECTION - functions

void	F_create(t_proc *data);
void	F_start(t_F *front, t_proc *data);
void	F_error(t_F *front, const char *err);
void	F_stop(t_F *front);
void	F_timeStart(t_F *front);
void	F_modeGame(t_F *front);
int		F_thread_mqueue(void *data);
void	F_load_media(t_F *front, int type, int size);
void	F_loop(t_F *front);
void	F_loop_matchmaking(t_F *front);
void	F_events_queue(t_F *front);
void	F_events_sdl(t_F *front);
void	F_render_reset(t_F *front);
void	F_render_grid(t_F *front);
void	F_txt_create(t_F *front, int id, const char *txt);