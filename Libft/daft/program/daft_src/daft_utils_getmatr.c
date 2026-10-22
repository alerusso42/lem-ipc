/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft_utils_getmatr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:11:28 by codespace         #+#    #+#             */
/*   Updated: 2026/04/23 12:23:01 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prog.h"

static void	*split_values(t_daft_data *data, t_daft_list *file, char *line);

/*
	2)	|yn=,		|	APPLE			|	{"Red,Yellow,Green", "2"}
*/
void	*_daft_get_vertical_matr(t_daft_data *data, t_daft_list *file)
{
	int		size;
	char	**matr;
	char	*line;
	int		i;

	size = 0;
	matr = ft_calloc(size + data->minimal_matrix_num, sizeof(char *));
	if (!matr)
		return (NULL);
	i = 0;
	line = gnl();
	while (line && !ft_strchr(line, file->field_sep[0]))
	{
		if (size == i)
			if (_daft_resize_matr(&matr, &size, data->minimal_matrix_num) != 0)
				return (FREE(line), NULL);
		matr[i] = ft_strdup(line + sub_strlen(line, file->field_sep, EXCLUDE));
		FREE(line);
		if (!matr[i++])
			return (free_matrix((void *)matr));
		line = gnl();
	}
	FREE(line);
	data->mem.ptr = matr;
	return (matr);
}

/*
	3)	|ny=,		|	Colors			|	{"Red", "Yellow", "Green"}
*/
void	*_daft_get_horiz_matr(t_daft_data *data, t_daft_list *file, char *key)
{
	char	**matr;

	matr = split_values(data, file, key);
	data->mem.ptr = matr;
	return (matr);
}

//	Trims the key_value_sep, FOURTH PARAM: ]nn=;
//	Split using value_sep, FIFTH PARAM: ]nn=;
static void	*split_values(t_daft_data *data, t_daft_list *file, char *line)
{
	int		i;
	char	**matr;

	i = sub_strlen(line, file->key_value_sep, EXCLUDE);
	i += sub_strlen(line + i, file->key_value_sep, INCLUDE);
	matr = _daft_split(line + i, *file->values_sep, \
	data->minimal_alloc_size, data->minimal_matrix_num);
	if (!matr)
		return (_daft_log(DAFT_LOG_MALLOC), NULL);
	matr[0] = ft_calloc(data->minimal_alloc_size + i + 1, sizeof(char));
	if (!matr[0])
		return (free_matrix((void *)matr), _daft_log(DAFT_LOG_MALLOC), NULL);
	sub_strcpy(matr[0], line, file->key_value_sep, EXCLUDE);
	return (matr);
}

/*
	4)	|yy=,		|	APPLE			|	{"Red", "Yellow", "Green"}, {"2"}
*/
void	*_daft_get_three_d_matr(t_daft_data *data, t_daft_list *file)
{
	int		size;
	char	***matr;
	char	*line;
	int		i;

	size = 4;
	matr = ft_calloc(size + 1, sizeof(char **));
	if (!matr)
		return (NULL);
	i = 0;
	line = gnl();
	while (line && !ft_strchr(line, file->field_sep[0]))
	{
		if (size == i)
			if (_daft_resize_three_d_matr(&matr, &size, data->minimal_matrix_num) != 0)
				return (FREE(line), NULL);
		matr[i] = split_values(data, file, line);
		FREE(line);
		if (!matr[i++])
			return (free_three_d_matrix((void *)matr));
		line = gnl();
	}
	FREE(line);
	data->mem.ptr = matr;
	return (matr);
}
