/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:56:36 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/27 17:26:51 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prep.h"

static char	*itoa_malloc_guard(t_daft_prep *data, int struct_i);

void	_daft_print_filedata(t_daft_prep *data)
{
	char	*file_size;

	switch_filedata(data->hash_fd);
	file_size = ft_itoa(data->hash_size);
	if (!file_size)
		_daft_prep_error(data, ER_MALLOC);
	ft_putstr_fd(file_size, data->hash_fd);
	ft_putstr_fd(" ", data->hash_fd);
	ft_putstr_fd(data->flags, data->hash_fd);
	FREE(file_size);
	switch_filedata(data->data_fd);
}

void	_daft_print_hash_table(t_daft_prep *data)
{
	char	*pos_string;
	int		struct_i;
	int		lowest_key;
	int		old_key;
	int		i;

	struct_i = 0;
	old_key = -1;
	lowest_key = -1;
	i = 1;
	_daft_find_lowest_key(data, &lowest_key, &struct_i);
	while (lowest_key != -1)
	{
		i = lowest_key;
		_daft_coll_upd(data, old_key, lowest_key, &i);
		old_key = lowest_key;
		pos_string = itoa_malloc_guard(data, struct_i);
		ft_putstr_fd(pos_string, data->hash_fd);
		FREE(pos_string);
		_daft_find_lowest_key(data, &lowest_key, &struct_i);
	}
}

static char	*itoa_malloc_guard(t_daft_prep *data, int struct_i)
{
	char	*str;

	str = ft_itoa(data->hash_table[struct_i].pos);
	if (!str)
		_daft_prep_error(data, ER_MALLOC);
	return (str);
}
