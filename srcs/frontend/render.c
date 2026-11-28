/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 21:10:04 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/28 14:40:07 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"

void	F_render_reset(t_F *front)
{
	char	*txt;

	SDL_RenderClear(front->sdl.renderer);
	if (front->info.is_playing == true)
		return (F_render_grid(front));
	for (int i = 0; i != MAX_SENTENCE; i++)
	{
		txt = front->sdl.sentence[i].text;
		if (!txt)
			txt = TEXTS_MATCHMAKING[i];
		F_txt_create(front, i, txt);
	}
}

void	F_render_grid(t_F *front)
{
	float		x;
	float		y;
	SDL_FRect	rect;
	SDL_FRect	sprite;

	rect.w = (float)front->sdl.win_x / front->match->map_x;
	rect.h = (float)front->sdl.win_y / front->match->map_y;
	grid_get_data(front->proc, front->map_copy, front->players_copy);
	for (int i = 0; i != front->match->map_area; i++)
	{
		x = i % front->match->map_x;
		y = i / front->match->map_x;
		rect.x = (float)front->sdl.win_x * (x / (float)front->match->map_x);
		rect.y = (float)front->sdl.win_y * (y / (float)front->match->map_y);
		if (grid_issquare_wall(front->proc, i) == true)
			SDL_RenderTexture(front->sdl.renderer, front->sdl.txt[T_WALL].ptr, NULL, &rect);
		else
			SDL_RenderTexture(front->sdl.renderer, front->sdl.txt[T_FLOOR].ptr, NULL, &rect);
	}
	sprite.h = 32;
	sprite.w = 32;
	sprite.x = 0;
	sprite.y = 0;
	rect.w -= ((int)rect.w % 32);
	rect.h -= ((int)rect.w % 32);
	for (int i = 0; i != front->match->player_num; i++)
	{
		rect.x = (float)front->sdl.win_x * (front->players[i].edge.x / (float)front->match->map_x);
		rect.y = (float)front->sdl.win_y * (front->players[i].edge.y / (float)front->match->map_y);
		SDL_RenderTexture(front->sdl.renderer, front->sdl.txt[T_KART_RED + front->players[i].info.team].ptr, &sprite, &rect);
	}
}
