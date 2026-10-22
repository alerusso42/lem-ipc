/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft_utils_hashfiles2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:06:24 by alerusso          #+#    #+#             */
/*   Updated: 2025/09/23 19:05:40 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prog.h"

static int	get_one(t_daft_node **node, char *offsets);

//	Reads all hash file.
//	Stores all hash values and associated offsets.
int	_daft_get_data2(t_daft_list *file)
{
	char	*line;

	line = gnl();
	if (line)
		file->first_node = (int)ft_atoi(line);
	while (line)
	{
		if (get_one(&file->node[(int)ft_atoi(line)], line) != 0)
			return (FREE(line), DAFT_LOG_MALLOC);
		FREE(line);
		line = gnl();
	}
	return (0);
}

//	All offsets are saved.
//	In case of collisions, a node is added with _daft_add_node_back.
//	If a hash_values from zero to hash_size has no offset, the node
//	in position of that hash_values is left to NULL.
static int	get_one(t_daft_node **node, char *offsets)
{
	bool	first_allocation;
	int		i;
	int		offset;

	first_allocation = true;
	i = sub_strlen(offsets, " :\t", EXCLUDE);
	i += sub_strlen(offsets + i, " :\t", INCLUDE);
	while (offsets[i])
	{
		offset = (int)ft_atoi(offsets + i);
		if (first_allocation == true)
		{
			if (_daft_start_list(node, offset) != 0)
				return (_daft_log(DAFT_LOG_MALLOC));
			first_allocation = false;
		}
		else
		{
			if (_daft_add_node_back(*node, offset) != 0)
				return (_daft_log(DAFT_LOG_MALLOC));
		}
		i += sub_strlen(offsets + i, " ", EXCLUDE);
		i += (offsets[i] != 0);
	}
	return (0);
}
