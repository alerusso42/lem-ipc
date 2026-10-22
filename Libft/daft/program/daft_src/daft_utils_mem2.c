/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft_utils_mem2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 22:38:07 by alerusso          #+#    #+#             */
/*   Updated: 2025/09/23 17:40:00 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prog.h"

static void			_daft_free_old_mem(t_daft_mem *mem);

int		_daft_add_mem(t_daft_data *data)
{
	t_daft_mem	*list;

	list = data->old_mem;
	while (list && list->next)
		list = list->next;
	if (list)
		list->next = ft_calloc(1, sizeof(t_daft_mem));
	else
		list = ft_calloc(1, sizeof(t_daft_mem));
	if (!list)
		return (_daft_log(DAFT_LOG_MALLOC));
	if (!data->old_mem)
		data->old_mem = list;
	list = _daft_old_mem_node(data, INT_MAX);
	*list = data->mem;
	data->mem_size++;
	return (0);
}

static void	free_all_mem(t_daft_data *data)
{
	t_daft_mem	*temp;
	t_daft_mem	*next;

	temp = data->old_mem;
	while (temp)
	{
		next = temp->next;
		_daft_free_old_mem(temp);
		temp = next;
	}
	data->old_mem = NULL;
	data->mem_size = -1;
}

void	_daft_free_mem(t_daft_data *data, int call_n)
{
	t_daft_mem	*temp;
	t_daft_mem	*to_delete;

	if (call_n < 0)
		return (free_all_mem(data));
	to_delete = _daft_old_mem_node(data, call_n);
	temp = _daft_old_mem_node(data, call_n - 1);
	if (temp && temp->next)
		temp->next = temp->next->next;
	else if (call_n == 0 && data->old_mem)
		temp = data->old_mem->next;
	_daft_free_old_mem(to_delete);
	if (call_n == 0)
		data->old_mem = temp;
	data->mem_size--;
	return ;

}

t_daft_mem	*_daft_old_mem_node(t_daft_data *data, int n)
{
	t_daft_mem	*mem;

	if (n < 0)
		return (NULL);
	mem = data->old_mem;
	while (mem && mem->next && n--)
		mem = mem->next;
	return (mem);
}

//REVIEW -	Last ptr given by daft_get() is stored in
//			data->mem. This ptr is freed on the next call
//			of daft_*.
static void	_daft_free_old_mem(t_daft_mem *mem)
{
	if (!mem || mem->type == NO_MEM)
		return ;
	else if (mem->type == STRING)
		FREE(mem->ptr);
	else if (mem->type == TWO_D_MATRIX)
		free_matrix(mem->ptr);
	else if (mem->type == THREE_D_MATRIX)
		free_three_d_matrix(mem->ptr);
	FREE(mem->key);
	FREE(mem);
}
