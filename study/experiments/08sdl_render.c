/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 13:15:42 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/27 17:17:20 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#define SDL_MAIN_USE_CALLBACKS 1
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1280

//NOTE - example taken from SDL/examples/renderer/06-textures

//NOTE - I really do not like this code architecture

//NOTE - usage
/*
export LD_LIBRARY_PATH=../../SDL/build
cc -Wall -Wextra -I ../../SDL/include/  *.c -Wl,-rpath=~/Desktop/sdl-tests/SDL/build ~/Desktop/sdl-tests/SDL/build/libSDL3.so 
*/

typedef struct s_data
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	int				status;
	int				txtr_w;
	int				txtr_h;
}		t_data;

SDL_AppResult SDL_AppIterate(t_data *data);
SDL_AppResult SDL_AppInit(t_data *data, int argc, char *argv[]);
void 			SDL_AppQuit(t_data *data, SDL_AppResult result);

int	main(int argc, char **argv)
{
	static t_data	data;

	if (SDL_AppInit(&data, argc, argv) != SDL_APP_CONTINUE)
		return (1);
	while (1)
	{
		if (SDL_AppIterate(&data) == SDL_APP_SUCCESS)
			return (SDL_AppQuit(&data, 0), 0);
		SDL_Delay(180);
	}
}

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(t_data *data, int argc, char *argv[])
{
	SDL_Surface *surface;

	(void)argc, (void)argv;
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) 
	{
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	if (!SDL_CreateWindowAndRenderer("examples/renderer/textures", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE, &data->window, &data->renderer)) 
	{
		SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	SDL_SetRenderLogicalPresentation(data->renderer, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);

	/* Textures are pixel data that we upload to the video hardware for fast drawing. Lots of 2D
	   engines refer to these as "sprites." We'll do a static texture (upload once, draw many
	   times) with data from a png file. */

	/* SDL_Surface is pixel data the CPU can access. SDL_Texture is pixel data the GPU can access.
	   Load a .png into a surface, move it to a texture from there. */
	surface = SDL_LoadPNG("./undertale.png");
	if (!surface) 
	{
		SDL_Log("Couldn't load png: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	data->txtr_w = surface->w;
	data->txtr_h = surface->h;
	data->texture = SDL_CreateTextureFromSurface(data->renderer, surface);
	SDL_DestroySurface(surface);  /* done with this, the texture has a copy of the pixels now. */
	if (!data->texture) 
	{
		SDL_Log("Couldn't create static texture: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent()
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_EVENT_KEY_DOWN)
		{
			SDL_Log("Pressed: %d\n", event.key.key);
			if (event.key.key == 27)
				return SDL_APP_SUCCESS;
		}
		if (event.type == SDL_EVENT_QUIT)
			return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
	}
	return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(t_data *data)
{
	SDL_FRect dst_rect;
	const Uint64 now = SDL_GetTicks();

	if (SDL_AppEvent() == SDL_APP_SUCCESS)
		return (SDL_APP_SUCCESS);
	/* we'll have some textures move around over a few seconds. */
	const float direction = ((now % 2000) >= 1000) ? 1.0f : -1.0f;
	const float scale = ((float) (((int) (now % 1000)) - 500) / 500.0f) * direction;

	/* as you can see from this, rendering draws over whatever was drawn before it. */
	SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* black, full alpha */
	SDL_RenderClear(data->renderer);  /* start with a blank canvas. */

	/* Just draw the static texture a few times. You can think of it like a
	   stamp, there isn't a limit to the number of times you can draw with it. */

	/* top left */
	dst_rect.x = (100.0f * scale);
	dst_rect.y = 0.0f;
	dst_rect.w = (float) data->txtr_w;
	dst_rect.h = (float) data->txtr_h;
	SDL_RenderTexture(data->renderer, data->texture, NULL, &dst_rect);

	/* center this one. */
	dst_rect.x = ((float) (WINDOW_WIDTH - data->txtr_h)) / 2.0f;
	dst_rect.y = ((float) (WINDOW_HEIGHT - data->txtr_h)) / 2.0f;
	dst_rect.w = (float) data->txtr_w;
	dst_rect.h = (float) data->txtr_h;
	SDL_RenderTexture(data->renderer, data->texture, NULL, &dst_rect);

	/* bottom right. */
	dst_rect.x = ((float) (WINDOW_WIDTH - data->txtr_w)) - (100.0f * scale);
	dst_rect.y = (float) (WINDOW_HEIGHT - data->txtr_h);
	dst_rect.w = (float) data->txtr_w;
	dst_rect.h = (float) data->txtr_h;
	SDL_RenderTexture(data->renderer, data->texture, NULL, &dst_rect);

	SDL_RenderPresent(data->renderer);  /* put it all on the screen! */
	return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(t_data *data, SDL_AppResult result)
{
	(void)data, (void)result;
	SDL_DestroyTexture(data->texture);
	SDL_DestroyRenderer(data->renderer);
	SDL_DestroyWindow(data->window);
	SDL_Quit();
	/* SDL will clean up the window/renderer for us. */
}

