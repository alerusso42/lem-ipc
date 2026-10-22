/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:12:50 by alerusso          #+#    #+#             */
/*   Updated: 2025/09/26 01:01:01 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prep.h"

void	_daft_prep_error(t_daft_prep *data, int err_type)
{
	_daft_prep_free_memory(data);
	if (data->exit)
		exit(err_type);
}

void	_daft_prep_free_memory(t_daft_prep *data)
{
	FREE(data->hash_table);
	FREE(data->collision);
	closefd(data->data_fd);
	closefd(data->hash_fd);
}

void	_daft_prep_alloc_memory(t_daft_prep *data)
{
	int	i;

	data->hash_table = (t_daft_hash *)\
	ft_calloc(data->hash_size + 22, sizeof(t_daft_hash));
	if (!data->hash_table)
		_daft_prep_error(data, ER_MALLOC);
	data->collision = (int *)ft_calloc(data->hash_size + 22, sizeof(int));
	if (!data->collision)
		_daft_prep_error(data, ER_MALLOC);
	i = -1;
	while (++i != data->hash_size)
		data->hash_table[i].key = -1;
}
