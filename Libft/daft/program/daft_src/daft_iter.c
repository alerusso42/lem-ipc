/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft_iter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 09:51:09 by alerusso          #+#    #+#             */
/*   Updated: 2026/01/16 23:33:52 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prog.h"

static void	*iterate_data(t_daft_list *list);
static char	*seek_file_first_line(t_daft_data *dt, t_daft_node *node, t_fd fd);

/*
//REVIEW -	daft_iter
- when called, returns the first database value.
- on a new call, returns the next value.
- on the last call, return NULL, and reset the iterator to start.

- param:	the address of a string
- ret:		true if a valid key is found, else false
*/
bool	daft_iter(void **ptr)
{
	t_daft_data	*dt;
	t_daft_node	*node;
	t_fd		fd;
	char		*first_line;

	dt = _daft_get_memory(NULL, false);
	if (!dt)
		return (_daft_log(DAFT_LOG_NOMEM), false);
	if (!ptr)
		return (_daft_log(DAFT_LOG_PARAM), false);
	node = iterate_data(dt->data_list[dt->current_file]);
	if (!node)
		return (false); 
	fd = openfd(dt->data_list[dt->current_file]->filename, "r");
	if (!fd.p)
		return (_daft_log(DAFT_LOG_OPEN), false);
	first_line = seek_file_first_line(dt, node, fd);
	if (!first_line)
		return (closefd(fd), _daft_log(DAFT_LOG_MALLOC), false);
	*ptr = _daft_select_mem_type(dt, dt->data_list[dt->current_file], first_line);
	closefd(fd);
	if (*ptr)
		return (_daft_add_mem(dt), true);
	else
		return (_daft_log(DAFT_LOG_ITER), false);
}

static void	*iterate_data(t_daft_list *list)
{
	static t_daft_node	*node;

	if (node)
	{
		node = node->next;
		if (!node)
			list->iterator++;
	}
	else
		node = list->node[list->iterator];
	while (!node && list->iterator != list->size)
	{
		node = list->node[list->iterator];
		if (!node)
			list->iterator++;
	}
	if (list->iterator == list->size)
		list->iterator = 0;
	return (node);
}

/*
char	*_daft_get_key(t_daft_data *dt, t_daft_list *f, const char *s, t_fd fd)
{
	int			hash_result;
	int			offset;
	t_daft_node	*current;
	char		*key;

	hash_result = _daft_hash(f, s);
	if (!f->node[hash_result])
		return (NULL);
	key = NULL;
	current = f->node[hash_result];
	while (!key && current)
	{
		offset = current->offset;
		SEEK(fd.p, offset, SEEK_SET);
		key = check_key(s, f->field_sep, &fd);
		current = current->next;
	}
	if (!key)
		return (NULL);
	dt->mem.file = dt->current_file;
	dt->mem.hash = hash_result;
	dt->mem.key = key;
	return (key);
}
*/
static char	*seek_file_first_line(t_daft_data *dt, t_daft_node *node, t_fd fd)
{
	char	*line;

	SEEK(fd.p, node->offset, SEEK_SET);
	line = gnl();
	if (!line)
		return (NULL);
	dt->mem.file = dt->current_file;
	dt->mem.hash = node->offset;
	dt->mem.key = line;
	return (line);
}
