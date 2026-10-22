/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:47:18 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/27 16:44:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n);

/*
int main(int argc, char *argv[])
{
    char    *destination;
    char    *source;
    size_t  n;
    
    if (argc < 3)
    {
        printf("INSERISCI: \nargv[1] = dest;\n");
        printf("argv[2] = source\n");
        printf("argv[3] = n bytes da muovere.\n");
        
        
        return (42);
    }
    source = argv[2];
    if (atoi(argv[3]) < 0)
    {
        printf("Allora, qui non siamo in villaggio ");
        printf("turistico, e tu non fai ridere.\n");
        return (42);
    }
    n = (size_t)atoi(argv[3]);
    destination = (char *)malloc(8 * sizeof(char));
    destination = ft_strcpy(destination, argv[1]);
    destination = (char *)ft_memmove((void *)destination,
	 (const void *)source, n);
    printf("\n%s\n", destination);
    free(destination);
    return (0);
}*/

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_ptr;
	unsigned char	*src_ptr;

	if ((!dest) || (!src))
		return (NULL);
	dest_ptr = (unsigned char *)dest;
	src_ptr = (unsigned char *)src;
	if ((src == dest) || (n == 0))
		return (dest);
	if (dest < src)
	{
		while (n--)
			*dest_ptr++ = *src_ptr++;
		return (dest);
	}
	if (dest > src)
	{
		dest_ptr += n;
		src_ptr += n;
		while (n--)
			*(--dest_ptr) = *(--src_ptr);
		return (dest);
	}
	else
		return (dest);
}
