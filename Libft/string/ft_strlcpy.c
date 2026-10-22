/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:29:30 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/20 20:35:46 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = 0;
	while (src[i++])
		++src_len;
	if (size == 0)
	{
		return (src_len);
	}
	i = 0;
	while ((src[i]) && (i < (size - 1)))
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
	return ((size_t)src_len);
}

/*
int    main(int argc, char *argv[])
{
    char    *src;
    char    dest[50];
    size_t  size;

    if ((argc < 3) || atoi(argv[2]) < 0)
    {
        printf("argv[1]: source \nargv[2]: size\n");
        return (42);
    }
    src = argv[1];
    dest[0] = '\0';
    size = (size_t)atoi(argv[2]);
	printf("Prima della modifica: ");
        printf("Size: %zu\n", size);
        printf("Src: %s\n", src);
   	    printf("Dest: %s\n", dest);
    printf("\nStrlcpy di Temu: \n");
    	printf("Byte copiati: %zu\n", ft_strlcpy(dest, src, size));
    	printf("Size: %zu\n", size);
   	printf("Src: %s\n", src);
   	printf("Dest: %s\n", dest);
    return (0);
}*/
