/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frontend.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:16:42 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/16 20:41:04 by alerusso42       ###   ########.fr       */
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
#define WINDOW_HEIGTH	1280
#define FPS				(double)60
#define FRAME_TIME		(int)((1000.0 / FPS) + 0.5)
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
typedef struct s_timer		t_timer;

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
	SDL_FRect	coords;
	int			timeout;
};

struct s_timer
{
	uint64_t	start;
	int64_t		curr;
	void		(*handler)(t_F*);
};

enum e_timer
{
	TIM_FPS,	
	TIM_SECOND,
	TIM_END,
	TIM_TEST,
	TIM_NUM
};

#define TIMERS_TIME	\
(const int [])\
{\
	[TIM_FPS] = FRAME_TIME, \
	[TIM_SECOND] = 1000, \
	[TIM_END] = 2000, \
	[TIM_TEST] = 5000, \
	[TIM_NUM] = 0 \
}

void	F_timeHandler_fps(t_F *front);
void	F_timeHandler_second(t_F *front);
void	F_timeHandler_endCheck(t_F *front);
void	F_timeHandler_test(t_F *front);

#define TIMERS_HANDLER	\
(void (*[])(t_F*))\
{\
	[TIM_FPS] = F_timeHandler_fps, \
	[TIM_SECOND] = F_timeHandler_second, \
	[TIM_END] = F_timeHandler_endCheck, \
	[TIM_TEST] = F_timeHandler_test, \
	[TIM_NUM] = NULL \
}

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
};

struct s_frontend
{
	t_sdl		sdl;
	t_timer		timers[TIM_NUM];//used with SDL_GetTicks to manage time events
	t_timer		clock;//used with SDL_GetTicks to record time
	t_proc		*proc;//process data
	int			fps;
	int			fps_count;//counter used to count frames; reset by TIM_SECOND
	bool		power_on;
};

//SECTION - functions

void	F_create(t_proc *data);
void	F_start(t_F *front, t_proc *data);
void	F_error(t_F *front, const char *err);
void	F_stop(t_F *front);
int		F_thread_mqueue(void *data);
void	F_load_media(t_F *front, int type, int size);
void	F_loop(t_F *front);
void	F_loop_matchmaking(t_F *front);
void	F_events_queue(t_F *front);
void	F_events_sdl(t_F *front);
void	F_time_checkAllTimers(t_F *front);
bool	F_time_checkTimer(t_F *front, t_timer *timer);
