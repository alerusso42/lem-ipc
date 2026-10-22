/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:17:31 by alerusso          #+#    #+#             */
/*   Updated: 2025/09/21 11:11:53 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prep.h"

static void	fill_one(t_daft_prep *data, char *line, int line_num, int cursor);

void	_daft_fill_hash_table(t_daft_prep *data)
{
	char	*line;
	int		bytes_read;
	int		line_num;
	int		i;
	int		cursor;

	bytes_read = 0;
	line_num = 1;
	i = 0;
	cursor = 0;
	line = gnl();
	while (line)
	{
		bytes_read += ft_strlen(line) + 1;
		i = sub_strlen(line, data->separator, EXCLUDE);
		if (line[i])
		{
			fill_one(data, line, line_num, cursor);
		}
		cursor = bytes_read;
		++line_num;
		FREE(line);
		line = gnl();
	}
}

static void	fill_one(t_daft_prep *data, char *line, int line_num, int cursor)
{
	data->hash_table[line_num].key = _daft_ft_hash(data, line);
	data->hash_table[line_num].pos = cursor;
	data->alloc_size++;
}
