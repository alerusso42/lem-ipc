/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 09:23:16 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/05 16:27:04 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"

//casts sdl cleanup functions
#define F_CAST (void (*)(void *))

static void	_clean(void **ptr, void(*f)(void *));
static void	_clean_arr(void **arr, void(*f)(void *), int size);

void	F_create(t_data *data)
{
	pid_t	pid;
	t_F		front;

	pid = fork();
	if (pid == -1)
		error(data, "fork failed");
	else if (pid != 0)
		return ;
	F_start(&front);
	F_loop_matchmaking(&front);
	F_stop(&front);
	cleanup(data);
	ft_printf("SDL: quit process\n");
	exit(0);
}

void	F_start(t_F *front)
{
	*front = (t_F){0};
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 1)
		F_error(front, "SDL init failed");
	if  (MIX_Init() != 1)
		F_error(front, "mixer init failed");
	if (TTF_Init() != 1)
		F_error(front, "mixer init failed");
	if (!SDL_CreateWindowAndRenderer("test", WINDOW_WIDTH, WINDOW_HEIGTH, \
	SDL_WINDOW_RESIZABLE, &front->sdl.window, &front->sdl.renderer)) 
		F_error(front, "window or renderer failed");
	front->sdl.mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
	if (!front->sdl.mixer)
		F_error(front, "mixer creation failed");
	front->sdl.text_engine = TTF_CreateRendererTextEngine(front->sdl.renderer);
	if (!front->sdl.text_engine)
		F_error(front, "txt engine cannot init");
	F_load_media(front, MEDIA_TEXTURE, TXT_NUM);
	F_load_media(front, MEDIA_SOUND, SOUND_MUSIC_NUM);
	F_load_media(front, MEDIA_FONT, FONTS_NUM);
	front->sdl.text_font = front->sdl.fonts[0].ptr;
}

void	F_error(t_F *front, const char *err)
{
	SDL_Log("\033[31mSDL ERROR \033[0m=> \"%s\": %s\n", err, SDL_GetError());
	F_stop(front);
	exit(1);
}

void	F_stop(t_F *front)
{
	t_data	data;

	data = (t_data){0};
	data.shared = front->shared;
	_clean((void **)&front->sdl.text_engine, F_CAST TTF_DestroyRendererTextEngine);
	_clean((void **)&front->sdl.track, F_CAST MIX_DestroyTrack);
	_clean((void **)&front->sdl.mixer, F_CAST MIX_DestroyMixer);
	_clean((void **)&front->sdl.renderer, F_CAST SDL_DestroyRenderer);
	_clean((void **)&front->sdl.window, F_CAST SDL_DestroyWindow);
	_clean_arr((void **)front->sdl.txt, F_CAST SDL_DestroyTexture, TXT_NUM);
	_clean_arr((void **)front->sdl.sounds, F_CAST MIX_DestroyAudio, SOUND_MUSIC_NUM);
	_clean_arr((void **)front->sdl.fonts, F_CAST TTF_CloseFont, FONTS_NUM);
	front->sdl.text_font = NULL;
	_clean_arr((void **)front->sdl.sentence, F_CAST SDL_DestroyTexture, MAX_SENTENCE);
	MIX_Quit();
	TTF_Quit();
	SDL_Quit();
	cleanup(&data);
}

//free sdl data, checking NULL and set to NULL
static void	_clean(void **ptr, void(*f)(void *))
{
	if (!*ptr)
		return ;
	f(*ptr);
	*ptr = NULL;
}

//free an array of struct with the data ptr as the first var, using _clean
//https://stackoverflow.com/questions/26818011/does-the-order-of-members-in-a-struct-matter
static void	_clean_arr(void **arr, void(*f)(void *), int size)
{
	if (!arr)
		return ;
	while (size--)
	{
		_clean(arr, f);
		arr++;
	}		
}
