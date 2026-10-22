/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:25:16 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/20 20:35:32 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#define UN_BOTTO 100

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/*
void	ft_uppercharacter(unsigned int index, char *c)
{
	c += index;
	if ((*c >= 'a') && (*c <= 'z') && (*c != '\0'))
		*c -= 32;
}


int	main()
{	
	char	*s;

	s = (char *)malloc(UN_BOTTO);
	if (!s)
		return (2);
	ft_strlcpy(s, "dslknsdlfbnwdljkfbwlfblsbf", UN_BOTTO);
	printf("\nStringa iniziale: \"%s\"\n", s);
	ft_striteri(s, *ft_uppercharacter);
	printf("Risultato: \"%s\"\n", s);
	free(s);
	return (0);
}*/
