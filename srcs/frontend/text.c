/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 19:54:05 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/19 11:59:29 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"

static void	_get_coord_by_id(t_F *front, int id, t_sentence *sentence);

/**
 * @brief display a text (to implement better)
 * 
 * @param front 
 * @param id 
 * @param txt 
 */
void	F_txt_create(t_F *front, int id, const char *txt)
{
	SDL_Color	color;
	SDL_Color	color2;
	SDL_Surface	*surface;
	t_sentence	*sentence;

	if (id < 0 || id >= MAX_SENTENCE)
		debug_log_int(front->proc, "Bug: Received a sentence with id %d", id);
	sentence = &front->sdl.sentence[id]; 
	if (sentence->ptr)
		SDL_DestroyTexture(sentence->ptr);
	sentence->ptr = NULL;
	color.a = 255;
	color.r = 255;
	color.b = 255;
	color.g = 255;
	color2.a = 255;
	color2.r = 0;
	color2.b = 0;
	color2.g = 0;
	_get_coord_by_id(front, id, sentence);
	surface = TTF_RenderText_LCD(front->sdl.text_font, txt, ft_strlen(txt), color, color2);
	if (!surface)
		F_error(front, "cannot create txt surface");
	sentence->ptr = SDL_CreateTextureFromSurface(front->sdl.renderer, surface);
	SDL_DestroySurface(surface);
	if (!sentence->ptr)
		F_error(front, "cannot create txt texture");
	SDL_RenderTexture(front->sdl.renderer, sentence->ptr, NULL, &sentence->coords);
}

static void	_get_coord_by_id(t_F *front, int id, t_sentence *sentence)
{
	(void)front, (void)id;
	sentence->coords.x = front->sdl.win_x / 10;
	sentence->coords.y = (float)front->sdl.win_y * (id / (float)MAX_SENTENCE);
	sentence->coords.w = front->sdl.win_x * 0.8;
	sentence->coords.h = 160;
	// debug_log_int_int(front->proc, "Print with x[%d], y[%d]", front->sdl.win_x, front->sdl.win_y);
	// debug_log_int_int(front->proc, "Print with x[%d], y[%d]", sentence->coords.x, sentence->coords.y);
	// debug_log_int_int(front->proc, "w[%d], h[%d]", sentence->coords.w, sentence->coords.h);
}
