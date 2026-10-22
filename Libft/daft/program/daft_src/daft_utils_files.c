/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft_utils_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:18:58 by alerusso          #+#    #+#             */
/*   Updated: 2025/09/25 22:36:15 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prog.h"

int	_daft_find_data_type(t_daft_list *file)
{
	if (file->multiple_lines == false && file->split_values == false)
	{
		return (STRING);
	}
	else if (file->multiple_lines == false && file->split_values == true)
	{
		return (TWO_D_MATRIX);
	}
	else if (file->multiple_lines == true && file->split_values == false)
	{
		return (TWO_D_MATRIX_VERTICAL);
	}
	else if (file->multiple_lines == true && file->split_values == true)
	{
		return (THREE_D_MATRIX);
	}
	return (NO_MEM);
}

int	_daft_open_files(t_daft_data *data, char *f_read, char *f_write)
{
	t_fd	fd_replace;
	t_fd	fd_file;

	if (data->temp_files[0].n || data->temp_files[1].n)
	{
		closefd(data->temp_files[0]);
		closefd(data->temp_files[1]);
	}
	fd_replace = openfd(f_write, "w");
	fd_file = openfd(f_read, "r");
	if (!fd_replace.n || !fd_file.n)
	{
		closefd(fd_replace);
		closefd(fd_file);
		return (1);
	}
	data->temp_files[1] = fd_replace;
	data->temp_files[0] = fd_file;
	return (0);
}

int	_daft_append_files(t_daft_data *data, char *f_read, char *f_write)
{
	t_fd	fd_replace;
	t_fd	fd_file;

	if (data->temp_files[0].n || data->temp_files[1].n)
	{
		closefd(data->temp_files[0]);
		closefd(data->temp_files[1]);
	}
	fd_replace = openfd(f_write, "a+");
	fd_file = openfd(f_read, "r");
	if (!fd_replace.n || !fd_file.n)
	{
		closefd(fd_replace);
		closefd(fd_file);
		return (1);
	}
	data->temp_files[1] = fd_replace;
	data->temp_files[0] = fd_file;
	return (0);
}
