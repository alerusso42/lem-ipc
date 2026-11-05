/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frontend.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:16:42 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/05 12:10:19 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
//SECTION - includes
#include "lem-ipc.h"
#include "media.h"
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

//SECTION - defines
#define WINDOW_WIDTH	1920
#define WINDOW_HEIGTH	1280
#define MAX_SENTENCE	5//maximum number of text in screen

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
typedef struct s_sentence	t_sentence;

struct s_textures
{
	SDL_Texture	*ptr;	
};

struct s_sounds
{
	MIX_Audio	*ptr;
};

struct s_sentence
{
	SDL_Texture	*ptr;
	SDL_FRect	coords;
	int			timeout;
};

struct s_sdl
{
	t_textures		txt[TXT_NUM];
	t_sounds		sound[SOUND_MUSIC_NUM];
	t_sentence		sentence[MAX_SENTENCE];
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	MIX_Mixer		*mixer;
	MIX_Track		*track;
	TTF_TextEngine	*text_engine;
	TTF_Font		*text_font;
};

struct s_frontend
{
	t_sdl			sdl;
	t_msg			msg;
	t_shared		*shared;
	int				msg_fd;
};

//SECTION - functions

void	F_start(t_F *front);
void	F_error(t_F *front, const char *err);
void	F_stop(t_F *front);