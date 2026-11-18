/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 21:10:04 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/18 21:14:34 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"

void	F_render_reset(t_F *front)
{
	char	*txt;

	SDL_RenderClear(front->sdl.renderer);
	for (int i = 0; i != MAX_SENTENCE; i++)
	{
		txt = front->sdl.sentence[i].text;
		if (!txt)
			txt = TEXTS_MATCHMAKING[i];
		F_txt_create(front, i, txt);
	}
}
