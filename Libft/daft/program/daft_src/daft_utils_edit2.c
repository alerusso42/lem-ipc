/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft_utils_edit2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:55:49 by alerusso          #+#    #+#             */
/*   Updated: 2026/03/22 20:28:59 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prog.h"

static t_daft_mem	*check_edit(t_daft_data *data, int list_n, char *line);
static void			rewrite_data(t_daft_data *data, int i);

static t_daft_mem	*check_edit(t_daft_data *data, int list_n, char *line)
{
	int			i;
	int			hash;
	t_daft_mem	*mem;

	data->mem.add = -1;
	if (*line == '#')
		return (NULL);
	else if (!ft_strchr(line, *data->data_list[list_n]->field_sep))
		return (NULL);
	i = data->mem_size;
	hash = _daft_hash(data->data_list[list_n], line);
	mem = _daft_old_mem_node(data, i--);
	while (mem)
	{
		if (mem->file == list_n && mem->hash == hash)
		{
			data->mem.add = i + 1;
			return (mem);
		}
		mem = _daft_old_mem_node(data, i--);
	}
	return (NULL);
}

int	_daft_update_data(t_daft_data *data, int i)
{
	char		*line;
	t_daft_mem	*edit;

	if (_daft_open_files(data, data->data_list[i]->filename, data->conf.tmp_path))
		return (1);
	line = gnl();
	while (line)
	{
		edit = check_edit(data, i, line);
		if (edit)
			_daft_edit_f(data, i, &line, edit);
		else
		{
			tfd_printf(data->temp_files[1], "%s\n", line);
			FREE(line);
			line = gnl();
		}
	}
	rewrite_data(data, i);
	return (closefd(data->temp_files[0]), closefd(data->temp_files[1]), 0);
}

static void	rewrite_data(t_daft_data *data, int i)
{
	char	*line;

	if (_daft_open_files(data, data->conf.tmp_path, data->data_list[i]->filename))
		return ;
	line = gnl();
	while (line)
	{
		tfd_printf(data->temp_files[1], "%s\n", line);
		FREE(line);
		line = gnl();
	}
}
