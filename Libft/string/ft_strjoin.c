/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:36:07 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 17:21:21 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*stringona;
	int		index;
	int		size;

	if ((!s1) || (!s2))
		return (NULL);
	index = 0;
	while (s1[index])
		++index;
	size = index;
	index = 0;
	while (s2[index])
		++index;
	size += index;
	stringona = NULL;
	stringona = (char *)CALLOC(size + 1, 1);
	if (!stringona)
		return (NULL);
	index = 0;
	stringona[0] = 0;
	while (*s1)
		stringona[index++] = *s1++;
	while (*s2)
		stringona[index++] = *s2++;
	return (stringona);
}

/*
MODE select which str should freed
MODE 0: free none
MODE 1:	free s1
MODE 2:	free s2
MODE 3:	free both
*/
char	*ft_strjoin_free(char *s1, char *s2, int mode)
{
	char	*join;

	if (s1 && !s2)
		join = ft_strdup(s1);
	else if (!s1 && s2)
		join = ft_strdup(s2);
	else
		join = ft_strjoin(s1, s2);
	if (mode == 1)
		FREE(s1);
	else if (mode == 2)
		FREE(s2);
	else if (mode > 2)
		FREE(s1), FREE(s2);
	return (join);
}

/*
int	main(int argc, char *argv[])
{
	char	*s1;
	char	*s2;
	char	*stringona;

	if (argc < 3)
	{
		printf("s1 = argv[1]; s2 = argv[2]");
		return (42);
	}
	s1= argv[1];
	s2 = argv[2];
	stringona = ft_strjoin(s1, s2);
	printf("\n STRINGHE\ns1: %s;\ns2: %s\n", s1, s2);
	printf("\n STRINGONA:%s\n", stringona);
	return (0);
}
*/
