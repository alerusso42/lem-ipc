/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:43:05 by alerusso          #+#    #+#             */
/*   Updated: 2025/09/26 18:56:52 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prog.h"

/*
//REVIEW -	daft_free
//
	Free a memory returned by daft, in a call of daft_get() or daft_edit().
	All memory got from daft are handled by an internal garbage
	collector, and freed when daft_quit() is called.
	However, if you need, you can free them safely before, passing
	the memory to this function.

	WARNING: 	if you free a ptr taken with daft_edit() or daft_append(),
				the file content will not be changed, since you erased
				the memory before calling daft_quit().
*/
void	daft_free(void *mem)
{
	t_daft_data	*data;
	int			i;

	data = _daft_get_memory(NULL, false);
	if (!data)
		return ((void)_daft_log(DAFT_LOG_NOMEM));
	if (!mem || !data->old_mem)
		return ;
	i = 0;
	while (data->old_mem[i].ptr)
	{
		if (mem == data->old_mem[i].ptr)
			_daft_free_mem(data, i);
		++i;
	}
}
