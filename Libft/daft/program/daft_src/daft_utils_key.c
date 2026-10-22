/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft_utils_key.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 22:55:32 by alerusso          #+#    #+#             */
/*   Updated: 2026/01/16 21:34:31 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prog.h"

static char	*check_key(const char *search, char field_sep[], t_fd *fd);

//	Gets hash from string
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

//	Check if key is right (for collisions).
static char	*check_key(const char *search, char field_sep[], t_fd *fd)
{
	char	*key;

	key = gnl();
	if (!key)
		return (NULL);
	if (!ft_strncmp(search, key, sub_strlen(key, field_sep, EXCLUDE)))
		return (key);
	FREE(key);
	get_static_buffer(fd->n, 1, 0);
	SEEK(fd->p, 0, 0);
	return (NULL);
}
