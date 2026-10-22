/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:49:22 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/27 19:56:38 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prep.h"

static int		file_size(t_daft_prep *data);

void	_daft_prep_parse_args(t_daft_prep *data, char *argv[])
{
	long long int	atoi_check;
	double			hash_size_modifier;

	data->data_fd = openfd(argv[1], "r");
	if (!data->data_fd.n)
		_daft_prep_error(data, ER_OPEN);
	data->hash_fd = openfd(argv[2], "w");
	if (!data->data_fd.n)
		_daft_prep_error(data, ER_OPEN);
	atoi_check = ft_atoi(argv[3]);
	if (atoi_check > INT_MAX || atoi_check < INT_MIN)
		_daft_prep_error(data, ER_ATOI);
	data->file_num = (int)atoi_check;
	ft_strlcpy(data->separator, argv[4], 2);
	data->flags = argv[5];
	if (!data->separator[0] || !data->flags[0])
		_daft_prep_error(data, ER_ATOI);
	_daft_make_float(data, argv[6], &hash_size_modifier);
	data->hash_size = file_size(data) * hash_size_modifier;
	if (!data->hash_size)
		_daft_prep_error(data, ER_ATOI);
}

static int	file_size(t_daft_prep *data)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;
	int		line_num;

	line_num = 0;
	bytes_read = readfd(data->data_fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = 0;
		line_num += _daft_count_char(buffer, '\n');
		bytes_read = readfd(data->data_fd, buffer, BUFFER_SIZE);
	}
	reset_fd(data->data_fd);
	return (line_num + 1);
}

//	this function is called as a bridge of daft_src and prep_src
int	_daft_prep_prog(char *filenames[2], char *flags, int f_num, int f_size)
{
	t_daft_prep	data;

	data = (t_daft_prep){0};
	data.file_num = f_num;
	data.flags = flags;
	*data.separator = *flags;
	data.data_fd = openfd(filenames[0], "r");
	if (!data.data_fd.n)
		return (_daft_prep_error(&data, ER_OPEN), 1);
	data.hash_fd = openfd(filenames[1], "w+");
	if (!data.hash_fd.n)
		return (_daft_prep_error(&data, ER_OPEN), 1);
	if (!f_size)
		data.hash_size = (int)(file_size(&data) * 1.3f);
	else
		data.hash_size = f_size;
	_daft_prep_alloc_memory(&data);
	switch_filedata(data.data_fd);
	_daft_fill_hash_table(&data);
	_daft_print_filedata(&data);
	_daft_print_hash_table(&data);
	_daft_prep_free_memory(&data);
	return (0);
}
