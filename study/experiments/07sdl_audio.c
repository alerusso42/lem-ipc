/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 13:15:42 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/27 16:07:07 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

//NOTE - usage
/*
export LD_LIBRARY_PATH=../../SDL/build
cc -Wall -Wextra -I ../../SDL/include/  *.c -Wl,-rpath=~/Desktop/sdl-tests/SDL/build ~/Desktop/sdl-tests/SDL/build/libSDL3.so 
*/

typedef struct s_data
{
	MIX_Mixer	*mixer;
	MIX_Track	*track;
	MIX_Audio	*audio;
	int			status;
}		t_data;

static void	setup(t_data *data);
static void	loop(t_data *data);
static void	end(t_data *data);
static void	error(t_data *data, const char *err);
static void	handler_sigint(int sig);

bool	run = true;

int	main()
{
	t_data	data;

	(void)error;
	data = (t_data){0};
	setup(&data);
	SDL_Log("Press ^C to exit..\n");
	loop(&data);
	end(&data);
}

static void	setup(t_data *data)
{
	signal(SIGINT, handler_sigint);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 1)
		error(data, "SDL init failed");
	if (MIX_Init() != 1)
		error(data, "mixer init failed");
	data->mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
	if (!data->mixer)
		error(data, "mixer creation failed");
	data->audio = MIX_LoadAudio(data->mixer, "./re-zero.mp3", false);
	if (!data->audio)
		error(data, "audio creation failed");
	data->track = MIX_CreateTrack(data->mixer);
	if (!data->track)
		error(data, "track creation failed");
	if (MIX_SetTrackAudio(data->track, data->audio) != 1)
		error(data, "setTrackAudio failed");
	if (MIX_PlayTrack(data->track, 0) != 1)
		error(data, "playTrack failed");
}

static void	loop(t_data *data)
{
	(void)data;
	while (run == true)
	{
		SDL_Delay(4000);
		MIX_PlayTrack(data->track, 0);
	}
}

static void	error(t_data *data, const char *err)
{
	SDL_Log("%s: %s\n", err, SDL_GetError());
	data->status = 1;
	return (end(data));
}

static void	end(t_data *data)
{
	MIX_DestroyAudio(data->audio);
	MIX_DestroyTrack(data->track);
	MIX_DestroyMixer(data->mixer);
	SDL_Quit();
	MIX_Quit();
	exit(data->status);
}

static void	handler_sigint(int sig)
{
	(void)sig;
	run = false;
}
