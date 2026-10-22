/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft_utils_getstr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:11:28 by codespace         #+#    #+#             */
/*   Updated: 2025/09/21 16:08:18 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prog.h"

/*
	1)	|nn=,		|	Colors			|	"Red,Yellow,Green"
*/
void	*_daft_get_string(t_daft_data *data, t_daft_list *file, char *key)
{
	char	*mem;
	int		size;

	size = ft_strlen(key) + data->minimal_alloc_size;
	mem = ft_calloc(size, sizeof(char));
	if (!mem)
		return (NULL);
	ft_strlcpy(mem, key, size - data->minimal_alloc_size + 1);
	data->mem.ptr = mem;
	return (mem + sub_strlen(mem, file->field_sep, EXCLUDE));
}
