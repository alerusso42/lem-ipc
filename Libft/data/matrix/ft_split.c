/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 12:31:27 by alerusso          #+#    #+#             */
/*   Updated: 2026/04/23 12:23:35 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

static int	ft_alloc(char ***strings, const char *s, char c, int s_num);
static int	how_many_strings(const char *str, char c, int *s_n, int *i);
static void	ft_copy(char **strings, const char *str, char c, int str_num);

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

char	**ft_split(char const *s, char c)
{
	char	**strings;
	char	**saveposition_pointer;
	int		i;
	int		str_num;

	strings = NULL;
	if (how_many_strings((char *)s, c, &str_num, &i) != 0)
		return (NULL);
	if ((ft_alloc(&strings, s, c, str_num) == 42) && (strings))
	{
		saveposition_pointer = strings;
		*strings = 0;
		while ((*strings))
		{
			FREE(*strings);
			*strings = NULL;
			strings++;
		}
		strings = saveposition_pointer;
		FREE(strings);
		strings = NULL;
	}
	if (strings)
		ft_copy(strings, (char *)s, c, str_num);
	return (strings);
}

static int	how_many_strings(const char *str, char c, int *s_n, int *i)
{
	if ((!str) || (c == 0))
		return (1);
	*i = 0;
	*s_n = 0;
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

static int	ft_alloc(char ***strings, const char *s, char c, int s_num)
{
	size_t	str_len;
	int		i;

	*strings = (char **)ft_calloc((s_num + 1), sizeof(char *));
	if (*strings == NULL)
		return (42);
	s_num = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while ((s[i] == c) && (s[i] != '\0'))
			++i;
		str_len = 0;
		while ((s[i] != '\0') && (s[i++] != c))
			++str_len;
		if (str_len != 0)
			(*strings)[s_num] = (char *)ft_calloc((str_len + 1), sizeof(char));
		if ((str_len != 0) && ((*strings)[s_num] == NULL))
			return (42);
		if (str_len != 0)
			++s_num;
	}
	(*strings)[s_num] = NULL;
	return (0);
}

static void	ft_copy(char **strings, const char *str, char c, int str_num)
{
	int	i_str;
	int	i_matrix;

	i_str = 0;
	str_num = 0;
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

//s will remain the same as it started
//matr_c: the separator of matrixes
//str_c: the separator of strings
char	***ft_multi_split(char *s, char matr_c, char str_c)
{
	int		count;
	int		i;
	char	***matr;
	char	*next_str;

	count = 1;
	next_str = ft_strchr(s, matr_c);
	while (next_str && ++count)
		next_str = ft_strchr(s, matr_c);
	matr = ft_calloc(count + 1, sizeof(char **));
	if (!matr)
		return (NULL);
	i = -1;
	while (++i != count)
	{
		next_str = ft_strchr(s, matr_c);
		if (next_str)
			next_str[0] = '\0';
		matr[i] = ft_split(s, str_c);
		if (next_str)
			next_str[0] = matr_c;
		if (!matr[i])
			return (free_three_d_matrix((void *)matr));
	}
	return (matr);
}
