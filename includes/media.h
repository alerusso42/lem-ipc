/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   media.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 10:15:46 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/24 16:45:05 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

//SECTION - defines
#define DIR_MEDIA 		"media/"
#define DIR_SOUNDS		DIR_MEDIA "sounds/"
#define DIR_TEXTURES	DIR_MEDIA "textures/"
#define DIR_FONTS		DIR_MEDIA "fonts/"

//SECTION - general utilities

enum e_media
{
	MEDIA_EXT_BMP = 0,
	MEDIA_EXT_JPG = 1,
	MEDIA_EXT_PNG = 2,
	MEDIA_EXT_NUM,
	MEDIA_SOUND 	= 1 << 0,	
	MEDIA_TEXTURE 	= 1 << 1,	
	MEDIA_FONT	 	= 1 << 2,
};

#define EXT_ALLOWED \
(const char *[]) \
{\
	[MEDIA_EXT_BMP] =	".bmp",	\
	[MEDIA_EXT_JPG] =	".jpg",	\
	[MEDIA_EXT_PNG] =	".png",	\
	[MEDIA_EXT_NUM] =	NULL	\
}

//SECTION - sounds and music

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

#define PATH_SOUNDS \
(const char *[])\
{\
	[S_START] = 		DIR_SOUNDS	"test.mp3", \
	[S_END] = 			DIR_SOUNDS	"test.mp3", \
	[S_BUMP] = 			DIR_SOUNDS	"test.mp3", \
	[S_WALL_CRASH] = 	DIR_SOUNDS	"test.mp3", \
	[S_DEATH] = 		DIR_SOUNDS	"test.mp3", \
	[S_ELIMINATION] = 	DIR_SOUNDS	"test.mp3", \
	[S_NEW_PLAYER] = 	DIR_SOUNDS	"test.mp3", \
	[S_DEL_PLAYER] = 	DIR_SOUNDS	"test.mp3", \
	[M_LOBBY] = 		DIR_SOUNDS	"test.mp3", \
	[M_GAME] = 			DIR_SOUNDS	"test.mp3", \
	[M_END] = 			DIR_SOUNDS	"test.mp3", \
	[SOUND_MUSIC_NUM] = NULL \
}

//SECTION - textures

enum e_textures
{
	T_WELCOME,
	T_KART_RED,
	T_KART_YELLOW,
	T_KART_GREEN,
	T_KART_BLUE,
	TXT_NUM	
};

#define PATH_TEXTURES \
(const char	*[])\
{\
	[T_WELCOME] = DIR_TEXTURES "test.jpg", \
	[T_KART_RED] = DIR_TEXTURES "kart-red.png", \
	[T_KART_YELLOW] = DIR_TEXTURES "kart-yellow.png", \
	[T_KART_GREEN] = DIR_TEXTURES "kart-green.png", \
	[T_KART_BLUE] = DIR_TEXTURES "kart-blue.png", \
	[TXT_NUM] = NULL \
}

//SECTION - fonts

enum e_fonts
{
	F_CITY_CONTRASTS,
	FONTS_NUM
};

#define PATH_FONTS \
(const char	*[FONTS_NUM + 1])\
{\
	[F_CITY_CONTRASTS] = DIR_FONTS "city_contrasts.ttf", \
	[FONTS_NUM] = NULL \
}

#define TEXTS_MATCHMAKING \
(char *[MAX_SENTENCE + 1])\
{\
	[0] = "lem-ipc",\
	[1] = "To Esc: press [X], [esc], ctrl-c on terminal",\
	[2] = "to start: press enter (game not implemented)",\
	[3] = "placeholder",\
	[4] = "I have to change this font"\
}
