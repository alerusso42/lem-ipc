/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:13:25 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 17:40:43 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	index;
	size_t	substring_lenght;
	size_t	size;
	char	*substring;

	substring_lenght = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	while ((s[start + substring_lenght]) && (substring_lenght < len))
		++substring_lenght;
	size = substring_lenght;
	substring = (char *)CALLOC(size + 1, 1);
	if (!substring)
		return (NULL);
	index = 0;
	while (index < substring_lenght)
	{
		substring[index] = s[start + index];
		++index;
	}
	substring[index] = '\0';
	return (substring);
}

t_str	*_str_substr(t_str *this, const t_str *other, int32_t start, int32_t end)
{
	str_sdup(this, other);
	return (str_cut(this, start, end));
}

/*
int	main(int argc, char *argv[])
{
	char	*sub_string;
	int		start;
	size_t	len;
	
	if (argc < 4)
	{
		printf("1) STRINGA; 2) START 3) LEN");
		return (42);	
	}
	start = atoi(argv[2]);
	len = (int)atoi(argv[3]);
	sub_string = ft_substr(argv[1], start, len);
	printf("\n%s\n", sub_string),
	free(sub_string);
	return (0);
}*/
