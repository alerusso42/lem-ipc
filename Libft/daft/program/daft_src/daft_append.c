/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft_append.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:28:21 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/27 17:23:14 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prog.h"

static void	*gen_sample(t_daft_data *data, t_daft_list *file, const char *key);
static int	key_used(t_daft_data *dt, t_daft_list *f, const char *s, t_fd fd);

/*
//REVIEW -	daft_append
//
	Appends new data at the end of a file in the user database.
	File chosen must be chosen using daft_switch().
	On success, returns a copy of the first data in the file; you can modify
	it as you want.
	When daft_load() or daft_quit() are called, every buffer returned with
	daft_append() are written at the end of the file, and freed from memory.
	Parameters:	
				key:		the key of the new data you need to write;
				size:		the size in memory of the strings allocated;
				mtr_number:	the number of matrix allocated.
				
	Therefore, if you need to store the data:
	RUNNER_GIOVANNI%
	speed=12 km/h
	endurance=25 km
	time training=30 minutes
	
	you should call:
	----------------------------------------------------
	char	**mtr;

	mtr = daft_append("RUNNER_GIOVANNI", 10, 3);
	if (!mtr)
		return (1);
	----------------------------------------------------
	10:	the size of the longest string, "30 minutes";
	3:	the number of matrix needed (speed, endurance, time training).

	If key already exist, daft_append() fails.
*/
void	*daft_append(const char *key, int size, int mtr_number)
{
	t_daft_data	*data;
	void		*mem;

	if (!key)
		return (NULL);
	if (size < 0)
		size = 0;
	if (mtr_number <= 0)
		mtr_number = 1;
	data = _daft_get_memory(NULL, false);
	if (!data)
		return ((void)_daft_log(DAFT_LOG_NOMEM), NULL);
	data->minimal_alloc_size = size;
	data->minimal_matrix_num = mtr_number;
	mem = gen_sample(data, data->data_list[data->current_file], key);
	data->minimal_alloc_size = 0;
	data->minimal_matrix_num = 1;
	if (mem)
		data->data_list[data->current_file]->append = true;
	return (mem);
}

static int	key_used(t_daft_data *dt, t_daft_list *f, const char *s, t_fd fd)
{
	void	*key;

	key = _daft_get_key(dt, f, s, fd);
	dt->mem.hash = 0;
	dt->mem.key = NULL;
	if (key)
	{
		free(key);
		return (true);
	}
	return (false);
}

static void	*gen_sample(t_daft_data *data, t_daft_list *file, const char *key)
{
	t_fd	fd;
	char	*line;
	void	*mem;
	int		i;

	i = file->first_node;
	fd = openfd(data->data_list[data->current_file]->filename, "r");
	if (!fd.n)
		return (NULL);
	if (key_used(data, file, key, fd))
		return (closefd(fd), _daft_log(DAFT_LOG_KEYUSED), NULL);
	SEEK(fd.p, file->node[i]->offset, SEEK_SET);
	line = gnl();
	if (!line)
		return (closefd(fd), NULL);
	mem = _daft_select_mem_type(data, file, line);
	FREE(line);
	closefd(fd);
	if (mem)
	{
		data->mem.file = data->current_file;
		data->mem.hash = i;
		data->mem.key = ft_strjoin(key, file->field_sep);
		data->mem.offset = file->node[i]->offset;
		_daft_add_mem(data);
	}
	return (mem);
}
