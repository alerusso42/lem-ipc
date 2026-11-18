/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_sdl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 20:34:57 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/18 19:43:44 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"

void	F_events_sdl(t_F *front)
{
	SDL_Event	*event;

	event = &front->sdl.event;
	while (SDL_PollEvent(event))
	{
		if (event->type == SDL_EVENT_KEY_DOWN)
		{
			debug_log_int(front->proc, "Pressed: %d\n", event->key.key);
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
	}
}
