/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_sdl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 20:34:57 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/16 20:40:54 by alerusso42       ###   ########.fr       */
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
			ft_printf("Pressed: %d\n", event->key.key);
			if (event->key.key == 27)
				front->power_on = false;
		}
		if (event->type == SDL_EVENT_QUIT)
			front->power_on = false;
	}
}
