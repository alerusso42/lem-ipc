/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft_utils_mem3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 10:59:37 by alerusso          #+#    #+#             */
/*   Updated: 2026/04/23 12:23:22 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prog.h"

static int	ft_alloc(char ***strings, const char *s, char c, int size[3]);
static int	how_many_strings(const char *str, char c, int *s_n, int *i);
static void	ft_copy(char **strings, const char *str, char c, int str_num);
static int	add_new_strings(char **strings, int size[3]);

/*
int main(int argc, char *argv[])
{
    char    **strings;
	int		i;

	if (argc != 3)
	{
		printf("argv[1] = string, argv[2] = charset\n");
		return (42);
	}
	printf("Str: %s\n", argv[1]);
    printf("Charset: \"%s\"\n", argv[2]);
    strings = ft_split((char const *)argv[1], argv[2]);
	i = 0;
	do
    	printf("Stringa %d: %s\n", i + 1, strings[i]);
	while (strings[i++] != NULL);
	return (0);
}*/

char	**_daft_split(char const *s, char c, int string_size, int matr_size)
{
	char	**strings;
	int		i;
	int		size[3];

	size[2] = matr_size;
	strings = NULL;
	if (how_many_strings((char *)s, c, &size[0], &i) != 0)
		return (NULL);
	size[1] = string_size + 1;
	if ((ft_alloc(&strings, s, c, size) == 42))
	{
		return (free_matrix((void *)strings));
	}
	ft_copy(strings, (char *)s, c, size[0]);
	if (add_new_strings(strings, size) == 1)
		return (free_matrix((void *)strings));
	return (strings);
}

//string number starts from 1, because key is matr[0]
static int	how_many_strings(const char *str, char c, int *s_n, int *i)
{
	if ((!str) || (c == 0))
		return (1);
	*i = 0;
	*s_n = 1;
	while (str[*i] != '\0')
	{
		while ((str[*i] == c) && (str[*i] != '\0'))
			++(*i);
		if (str[*i] != c)
			++(*s_n);
		while ((str[*i] != c) && (str[*i] != '\0'))
			++(*i);
	}
	return (0);
}

static int	ft_alloc(char ***strings, const char *s, char c, int size[3])
{
	size_t	str_len;
	int		i;
	int		s_num;

	*strings = (char **)ft_calloc((size[0] + size[2]), sizeof(char *));
	if (*strings == NULL)
		return (42);
	s_num = 1;
	i = 0;
	while (s[i] != '\0')
	{
		while ((s[i] == c) && (s[i] != '\0'))
			++i;
		str_len = 0;
		while ((s[i] != '\0') && (s[i++] != c))
			++str_len;
		if (str_len != 0)
			(*strings)[s_num] = \
			(char *)ft_calloc((str_len + size[1]), sizeof(char));
		if ((str_len != 0) && ((*strings)[s_num] == NULL))
			return (42);
		s_num += (str_len != 0);
	}
	(*strings)[s_num] = NULL;
	return (0);
}

//index starts from 1, because key is matr[0]
static void	ft_copy(char **strings, const char *str, char c, int str_num)
{
	int	i_str;
	int	i_matrix;

	if (!strings)
		return ;
	i_str = 0;
	str_num = 1;
	while (str[i_str] != '\0')
	{
		i_matrix = 0;
		while ((str[i_str] == c) && (str[i_str] != '\0'))
			++i_str;
		while ((str[i_str] != c) && (str[i_str] != '\0'))
		{
			strings[str_num][i_matrix] = str[i_str];
			++i_matrix;
			++i_str;
		}
		if (strings[str_num] != NULL)
			strings[str_num][i_matrix] = '\0';
		if (i_matrix != 0)
			++str_num;
	}
	strings[str_num] = NULL;
}

//index starts from 1, because key is matr[0]
static int	add_new_strings(char **strings, int size[3])
{
	int	i;
	int	total_size;

	i = 1;
	total_size = size[0] + size[2] - 1;
	while (i < total_size)
	{
		if (!strings[i])
			strings[i] = (char *)ft_calloc((size[1] + 1), sizeof(char));
		if (!strings[i])
			return (1);
		++i;
	}
	return (0);
}
