/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:59:36 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/20 20:36:10 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*stock_ptr;
	unsigned char	casted_c;

	stock_ptr = NULL;
	casted_c = (unsigned char)c;
	while (*s != '\0')
	{
		if (*s == casted_c)
		{
			stock_ptr = (unsigned char *)s;
		}
		++s;
	}
	if (casted_c == 0)
		stock_ptr = (unsigned char *)s;
	return ((char *)stock_ptr);
}

/*
int main()
{
    printf("%s\n", ft_strrchr("mega_rayquaza mega assurdo", 'm'));
    return (0);
}*/
