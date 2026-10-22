/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft_utils_append.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:07:11 by alerusso          #+#    #+#             */
/*   Updated: 2026/01/05 17:40:15 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prog.h"

static void	append(t_daft_data *dt, t_daft_mem *mem, int fn);

void	_daft_append_data(t_daft_data *data, t_daft_list *file, int file_n)
{
	t_daft_mem	*mem;
	t_daft_mem	*next;
	int			i;

	if (_daft_append_files(data, file->filename, file->filename))
		return ;
	i = 0;
	mem = data->old_mem;
	while (mem)
	{
		next = mem->next;
		data->mem.add = i;
		if (mem->offset)
			append(data, mem, file_n);
		else
			i++;
		mem = next;
	}
	closefd(data->temp_files[0]);
	closefd(data->temp_files[1]);
}

static void	append(t_daft_data *dt, t_daft_mem *mem, int fn)
{
	char	*line;

	SEEK(dt->temp_files[0].p, mem->offset, SEEK_SET);
	line = gnl();
	if (!line)
	{
		_daft_free_mem(dt, dt->mem.add);
		return ;
	}
	tfd_printf(dt->temp_files[1], "\n");
	_daft_append_f(dt, fn, &line, mem);
	FREE(line);
}

