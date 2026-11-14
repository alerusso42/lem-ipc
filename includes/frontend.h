/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frontend.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:16:42 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/14 20:05:53 by alerusso42       ###   ########.fr       */
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
};

enum e_timer
{
	TIM_FPS,	
	TIM_SECOND,
	TIM_TEST,
	TIM_NUM	
};

#define TIMERS_TIME	\
(const int [])\
{\
	[TIM_FPS] = FRAME_TIME, \
	[TIM_SECOND] = 1000, \
	[TIM_TEST] = 5000, \
	[TIM_NUM] = 0 \
}

struct s_sdl
{
	t_textures		txt[TXT_NUM];
	t_sounds		sounds[SOUND_MUSIC_NUM];
	t_fonts			fonts[FONTS_NUM];
	t_sentence		sentence[MAX_SENTENCE];
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	MIX_Mixer		*mixer;
	MIX_Track		*track;
	TTF_TextEngine	*text_engine;
	TTF_Font		*text_font;
	SDL_Mutex		*mutex;
	SDL_Thread		*thread_mqueue;
};

struct s_frontend
{
	t_sdl		sdl;
	t_msg		msg;//THREAD RESERVED - buffer with the msg received
	t_timer		timers[TIM_NUM];//used with SDL_GetTicks to manage time events
	t_timer		clock;//used with SDL_GetTicks to record time
	t_shared	*shared;
	t_list		*msg_list;//THREAD UNSAFE - list of msg from mqueue thread
	t_list		*msg_last;//THREAD UNSAFE - list of msg from mqueue thread
	t_list		*msg_parsed;//curr msg parsed node
	int			msg_fd;
	int			fps;
	bool		power_on;//THREAD UNSAFE
};

//SECTION - functions

void	F_create(t_data *data);
void	F_start(t_F *front);
void	F_error(t_F *front, const char *err);
void	F_stop(t_F *front);
int		F_thread_mqueue(void *data);
void	F_load_media(t_F *front, int type, int size);
void	F_loop(t_F *front);
void	F_loop_matchmaking(t_F *front);
void	F_events_queue(t_F *front);
void	F_time_update(t_F *front);
bool	F_time_checkTimer(t_F *front, int id);
void	F_time_waitTimer(t_F *front, int id);
size_t	F_mutexCs(t_F *front, size_t(*f)(t_F *));
size_t	F_mutex_runCheck(t_F *front);
size_t	F_mutex_runStop(t_F *front);
size_t	F_mutex_getNextMsg(t_F *front);
size_t	F_mutex_delCurrMsg(t_F *front);
size_t	F_mutex_addMsg(t_F *front);
