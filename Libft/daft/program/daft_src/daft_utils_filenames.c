/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft_utils_filenames.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:50:37 by alerusso          #+#    #+#             */
/*   Updated: 2026/01/02 11:01:59 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prog.h"

static int	parse_fnames(t_daft_data *data, char *line, int *matr_s);

//	This function takes the filenames from settings file, and saves them
//	in a char ** matrix.
//	Skips all lines found after the delimiter "# -- FLAGS -- #"
//	that are either empty or comments '#'.
int	_daft_save_fnames(t_daft_data *data)
{
	bool	found_files;
	int		matr_s;
	char	*line;

	found_files = false;
	matr_s = 0;
	line = gnl();
	while (line)
	{
		if (found_files && line[0] == '#')
			break ;
		else if (!ft_strncmp(line, "# -- FLAGS -- #", 15))
			found_files = true;
		else if (parse_fnames(data, line, &matr_s) == DAFT_LOG_MALLOC)
		{
			FREE(line);
			return (DAFT_LOG_MALLOC);
		}
		FREE(line);
		line = gnl();
	}
	FREE(line);
	return (0);
}

//	Trim flags (->), resize matrix if necessary, 
//increase data->files_num.
static int	parse_fnames(t_daft_data *data, char *line, int *matr_s)
{
	int		len;
	char	*temp;

	if (!*line || *line == '#')
		return (0);
	len = 0;
	while (line[len] && ft_strncmp(line + len, "->", 2))
		++len;
	cut_string(line, len, INT_MAX);
	if (data->files_num == *matr_s)
		if (_daft_resize_matr(&data->files_names, matr_s, 1) == DAFT_LOG_MALLOC)
			return (_daft_log(DAFT_LOG_MALLOC));
	data->files_names[data->files_num] = ft_strjoin("/", line);
	if (!data->files_names[data->files_num])
		return (_daft_log(DAFT_LOG_MALLOC));
	temp = data->files_names[data->files_num];
	data->files_names[data->files_num] = \
	ft_strjoin(data->conf.path, data->files_names[data->files_num]);
	if (!data->files_names[data->files_num])
		return (FREE(temp), _daft_log(DAFT_LOG_MALLOC));
	FREE(temp);
	data->files_num += 1;
	return (0);
}
