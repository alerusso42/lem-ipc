/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_sdl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 20:34:57 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/19 11:53:43 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"

/**
 * @brief Loops through SDL_PollEvent, the SDL utilities to intercept external
 * events (user input, window resize, new device, quit...)
 * 
 * @param front 
 */
void	F_events_sdl(t_F *front)
{
	SDL_Event	*event;

	event = &front->sdl.event;
	while (SDL_PollEvent(event))
	{
		if (event->type == SDL_EVENT_KEY_DOWN)
		{
			debug_log_int(front->proc, "Pressed: %d", event->key.key);
			F_txt_create(front, 3, "      input!     ");
			if (event->key.key == SDLK_ESCAPE)
			{
				msg_sendAll(front->proc, MSGE_QUIT, NULL);
				front->power_on = false;
			}
			else if (event->key.key == 13)//enter
			{
				msg_sendId(front->proc, MSGID_MASTER, MSGE_START, NULL);
				debug_log(front->proc, "request matchmaking done.");
			}
		}
		else if (event->type == SDL_EVENT_QUIT)
		{
			msg_sendAll(front->proc, MSGE_QUIT, NULL);
			front->power_on = false;
		}
		else if (event->type == SDL_EVENT_WINDOW_RESIZED)
		{
			debug_log(front->proc, "Resizing screen...");
			SDL_GetWindowSize(front->sdl.window, &front->sdl.win_x, &front->sdl.win_y);
			F_render_reset(front);
		}
	}
}
