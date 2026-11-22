/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 09:23:16 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/22 20:12:53 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"

//casts sdl cleanup functions
#define F_CAST (void (*)(void *))

static void	_clean(void **ptr, void(*f)(void *));
static void	_clean_arr(void **arr, void(*f)(void *), int size);
static void	_free_sentence(t_sentence *sentence);

//create the frontend process using fork. Manages its cleanup
void	F_create(t_proc *data)
{
	pid_t	pid;
	t_F		front;

	pid = fork();
	if (pid == -1)
		error(data, "fork failed");
	else if (pid != 0)
		return ;
	sem_wait(&data->shared->s_gen);
	data->shared->n_client += 1;
	sem_post(&data->shared->s_gen);
	F_start(&front, data);
	debug_log(data, "start engine");
	F_loop(&front);
	F_stop(&front);
	cleanup(data);
	exit(0);
}

//initialize process and sdl data for frontend
void	F_start(t_F *front, t_proc *data)
{
	*front = (t_F){0};
	front->power_on = true;
	front->proc = data;
	data->info.is_master = false;
	data->id = MSGID_FRONT;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 1)
		F_error(front, "SDL init failed");
	if  (MIX_Init() != 1)
		F_error(front, "mixer init failed");
	if (TTF_Init() != 1)
		F_error(front, "mixer init failed");
	if (!SDL_CreateWindowAndRenderer("test", WINDOW_WIDTH, WINDOW_HEIGTH, \
	SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED, &front->sdl.window, &front->sdl.renderer)) 
		F_error(front, "window or renderer failed");
	if (!SDL_GetWindowSize(front->sdl.window, &front->sdl.win_x, &front->sdl.win_y))
		F_error(front, "cannot get window size");
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
	F_timeStart(front);
}

//display the error, cleanup and exit
void	F_error(t_F *front, const char *err)
{
	front->proc->info.error = true;
	debug_log_char_char(front->proc, "SDL ERROR => \"%s\": %s", err, SDL_GetError());
	F_stop(front);
	exit(1);
}

//cleanup sdl data
void	F_stop(t_F *front)
{
	_clean((void **)&front->sdl.text_engine, F_CAST TTF_DestroyRendererTextEngine);
	_clean((void **)&front->sdl.track, F_CAST MIX_DestroyTrack);
	_clean((void **)&front->sdl.mixer, F_CAST MIX_DestroyMixer);
	_clean((void **)&front->sdl.renderer, F_CAST SDL_DestroyRenderer);
	_clean((void **)&front->sdl.window, F_CAST SDL_DestroyWindow);
	_clean_arr((void **)front->sdl.txt, F_CAST SDL_DestroyTexture, TXT_NUM);
	_clean_arr((void **)front->sdl.sounds, F_CAST MIX_DestroyAudio, SOUND_MUSIC_NUM);
	_clean_arr((void **)front->sdl.fonts, F_CAST TTF_CloseFont, FONTS_NUM);
	front->sdl.text_font = NULL;
	for (int i = 0; i != MAX_SENTENCE; i++)
		_free_sentence(&front->sdl.sentence[i]);
	lst_clear(&front->proc->msg_list, free);
	MIX_Quit();
	TTF_Quit();
	SDL_Quit();
	_clean((void **)&front->map_render, free);
}

void	F_modeGame(t_F *front)
{
	char	*heap;

	if (shm_update(front->proc) == false)
		F_error(front, "cannot update shared memory");
	heap = front->proc->shared->heap;
	front->map = (t_grid *)heap;
	front->players = (t_player *)(heap + front->proc->shared->offset_player);
	front->match = &front->proc->shared->match;
	front->proc->map = front->map;
	front->proc->players = front->players;
	if (grid_copy(front->proc, &front->map_render) == false)
		F_error(front, "cannot copy shared map");
	front->info.is_playing = true;
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
		_clean(arr, (void *)f);
		arr++;
	}		
}

//free a t_sentence
static void	_free_sentence(t_sentence *sentence)
{
	SDL_DestroyTexture(sentence->ptr);
	free(sentence->text);
	*sentence = (t_sentence){0};
}
