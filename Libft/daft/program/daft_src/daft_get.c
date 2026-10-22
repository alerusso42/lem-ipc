/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 08:44:50 by codespace         #+#    #+#             */
/*   Updated: 2025/09/26 18:56:40 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prog.h"

/*
//REVIEW -	daft_get
//
	Takes a string as parameter. Gives back memory, or NULL.
	Fds are open and closed, without fd leaks.

	Memory returned depends on flags in SETTINGS.md.

	1)	*nn**:	Returns a regular string (char *);
	2)	*yn**:	Returns a 2D matrix(char **);
	3)	*ny**:	Returns a 2D matrix(char **);
	4)	*yy**:	Returns a 3D matrix(char ***);

	Example:
	...
	APPLE|
	Colors=Red,Yellow,Green
	Id=2
	...
	FLAGS GIVEN		|	SEARCH CONTENT	|	RETURNS
------------------------------------------------------------
	1)	|nn=,		|	Colors			|	"Red,Yellow,Green"
	2)	|yn=,		|	APPLE			|	{"Red,Yellow,Green", "2"}
	3)	|ny=,		|	Colors			|	{"Red", "Yellow", "Green"}
	4)	|yy=,		|	APPLE			|	{"Red", "Yellow", "Green"}, {"2"}
*/
void	*daft_get(const char *search)
{
	t_daft_data	*data;
	t_fd		fd;
	void		*mem;
	char		*key;

	if (!search)
		return (NULL);
	data = _daft_get_memory(NULL, false);
	if (!data)
		return (_daft_log(DAFT_LOG_NOMEM), NULL);
	fd = openfd(data->data_list[data->current_file]->filename, "r");
	if (!fd.n)
		return (NULL);
	key = _daft_get_key(data, data->data_list[data->current_file], search, fd);
	if (!key)
		return (NULL);
	mem = _daft_select_mem_type(data, data->data_list[data->current_file], key);
	closefd(fd);
	if (mem)
		_daft_add_mem(data);
	return (mem);
}

void	*_daft_select_mem_type(t_daft_data *data, t_daft_list *file, char *key)
{
	int	type;

	type = _daft_find_data_type(file);
	if (type == STRING)
	{
		data->mem.type = STRING;
		return (_daft_get_string(data, file, key));
	}
	else if (type == TWO_D_MATRIX)
	{
		data->mem.type = TWO_D_MATRIX;
		return (_daft_get_horiz_matr(data, file, key));
	}
	else if (type == TWO_D_MATRIX_VERTICAL)
	{
		data->mem.type = TWO_D_MATRIX;
		return (_daft_get_vertical_matr(data, file));
	}
	else if (type == THREE_D_MATRIX)
	{
		data->mem.type = THREE_D_MATRIX;
		return (_daft_get_three_d_matr(data, file));
	}
	data->mem.type = NO_MEM;
	return (NULL);
}
