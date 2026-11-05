/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_media.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 14:10:10 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/05 20:27:16 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"

#define ERR_PATH "Media load failure for path "

static SDL_Surface	*_get_texture_surface(const char *path);

//load media
void	F_load_media(t_F *front, int type, int size)
{
	int			i;
	bool		failure;
	SDL_Surface	*surface;
	const char	*path;

	i = 0;
	failure = true;
	while (i != size)
	{
		switch (type)
		{
			case (MEDIA_SOUND):
				path = PATH_SOUNDS[i];
				front->sdl.sounds[i].ptr = MIX_LoadAudio(front->sdl.mixer, path, false);
				failure = front->sdl.sounds[i].ptr == NULL;
				break ;
			case (MEDIA_TEXTURE):
				path = PATH_TEXTURES[i];
				surface = _get_texture_surface(path);
				front->sdl.txt[i].ptr = SDL_CreateTextureFromSurface(front->sdl.renderer, surface);
				SDL_DestroySurface(surface);
				failure = front->sdl.txt[i].ptr == NULL;
				break ;
			case (MEDIA_FONT):
				path = PATH_FONTS[i];
				front->sdl.fonts[i].ptr = TTF_OpenFont(path, 50);
				failure = front->sdl.fonts[i].ptr == NULL;
				break ;
		}
		if (failure)
			F_error(front, path);
		i++;
	}
}

static SDL_Surface	*_get_texture_surface(const char *path)
{
	char	*ext;
	int		len;

	ext = ft_strrstr(path, ".");
	if (!ext)
		return (NULL);
	len = ft_strlen(ext);
	for (int j = 0; EXT_ALLOWED[j]; j++)
	{
		if (ft_strncmp(ext, EXT_ALLOWED[j], len) != 0)
			continue ;
		switch (j)
		{
			case (MEDIA_EXT_BMP):
				return (SDL_LoadBMP(path));
			case (MEDIA_EXT_JPG):
				return (SDL_LoadJPG(path));
			case (MEDIA_EXT_PNG):
				return (SDL_LoadPNG(path));
			default :
				return (NULL);
		}
	}
	return (NULL);
}
