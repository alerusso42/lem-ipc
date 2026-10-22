/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:06:42 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/20 20:35:57 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*s2;

	i = 0;
	s2 = (char *)MALLOC(sizeof(char) * ft_strlen(s) + 1);
	if (!s2)
		return (NULL);
	while (s[i])
	{
		s2[i] = f(i, s[i]);
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

/*
int	main()
{	
	char	*s = "JolL7y";

	printf("\nStringa iniziale: \"%s\"\n", s);
	s = ft_strmapi(s, *ft_uppercharacter);
	printf("Risultato: \"%s\"\n", s);
	free(s);
	return (0);
}*/
