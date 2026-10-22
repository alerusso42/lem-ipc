/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft_utils_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 22:38:07 by alerusso          #+#    #+#             */
/*   Updated: 2025/09/23 11:01:52 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prog.h"

//REVIEW - 	if update == true, the static ptr is set to new_data.
//			always returns static ptr.
t_daft_data	*_daft_get_memory(t_daft_data *new_data, bool update)
{
	static t_daft_data	*ptr;

	if (update)
		ptr = new_data;
	return (ptr);
}

//REVIEW - 	Takes the ptr of a 2D matrix.
//			Reallocs it, increasing its size.
//			If old size (*size) is == 0, *size becomes 2;
//			Else, *size is doubled.
int			_daft_resize_matr(char ***old_matr, int *size, int min_alloc)
{
	char	**new_matr;
	int		i;

	if (!old_matr || !size)
		return (DAFT_LOG_MALLOC);
	if (!*size)
		*size = 2;
	else
		*size = *size * 2;
	new_matr = ft_calloc(*size + min_alloc, sizeof(char *));
	if (!new_matr)
		return (FREE(*old_matr), DAFT_LOG_MALLOC);
	i = 0;
	while ((*old_matr) && (*old_matr)[i])
	{
		new_matr[i] = (*old_matr)[i];
		++i;
	}
	FREE(*old_matr);
	*old_matr = new_matr;
	return (0);
}

//REVIEW - 	ft_lstnew. Initializes with offset.
int	_daft_start_list(t_daft_node **list, int offset)
{
	*list = ft_calloc(1, sizeof(t_daft_node));
	if (!*list)
		return (1);
	(*list)->offset = offset;
	return (0);
}

//REVIEW - 	ft_lst_add_back. Initializes with offset.
int	_daft_add_node_back(t_daft_node	*list, int offset)
{
	t_daft_node	*node;

	node = ft_calloc(1, sizeof(t_daft_node));
	if (!node)
		return (1);
	node->offset = offset;
	while (list->next)
		list = list->next;
	list->next = node;
	return (0);
}

//REVIEW - 	Takes the ptr of a 3D matrix.
//			Reallocs it, increasing its size.
//			If old size (*size) is == 0, *size becomes 2;
//			Else, *size is doubled.
int	_daft_resize_three_d_matr(char ****old_matr, int *size, int min_alloc)
{
	char	***new_matr;
	int		i;

	if (!old_matr || !*old_matr || !size)
		return (DAFT_LOG_MALLOC);
	if (!*size)
		*size = 2;
	else
		*size = *size * 2;
	new_matr = ft_calloc(*size + min_alloc, sizeof(char **));
	if (!new_matr)
		return (FREE(*old_matr), DAFT_LOG_MALLOC);
	i = 0;
	while ((*old_matr)[i])
	{
		new_matr[i] = (*old_matr)[i];
		++i;
	}
	FREE(*old_matr);
	*old_matr = new_matr;
	return (0);
}
