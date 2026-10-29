/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_graphic_sound.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:16:42 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/29 12:30:49 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_GRAPHIC_SOUND_H
# define SDL_GRAPHIC_SOUND_H
//SECTION - includes
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
//SECTION - defines
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1280

//SECTION - data structures
typedef struct s_sdl	t_sdl;
typedef struct s_sounds	t_sounds;

enum e_sounds
{
	S_START,	
	S_END,
	S_BUMP,
	S_WALL_CRASH,
	S_DEATH,
	S_ELIMINATION,
	S_NEW_PLAYER,
	S_DEL_PLAYER,
	M_LOBBY,
	M_GAME,
	M_END,
	SOUND_MUSIC_NUM	
};

struct s_sdl
{
	t_sounds		sounds[SOUND_MUSIC_NUM];
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	MIX_Mixer		*mixer;
	int				txtr_w;
	int				txtr_h;
};

struct s_sounds
{
	MIX_Mixer		*mixer;
	MIX_Track		*track;
};

#endif