/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:44:58 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/20 20:35:41 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
int	main(int argc, char *argv[])
{
	unsigned int	size;

    if (argc < 4)
    {
        printf("\nargv[1] = stringa 1\nargv[2] = stringa 2");
        printf("\nargv[3] = size");
        return (42);    
    }
    size = atoi(argv[3]);
    //strlcat(argv[1], argv[2], size);
	ft_strlcat(argv[1], argv[2], size);
	printf("Ecco qua campione: %s", argv[1]);
	return (0);
}*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	if (size < dest_len)
		return (src_len + size);
	i = 0;
	while (((i + dest_len) < size - 1) && (src[i] != '\0'))
	{
		dst[dest_len + i] = src[i];
		++i;
	}
	dst[dest_len + i] = '\0';
	return (dest_len + src_len);
}
