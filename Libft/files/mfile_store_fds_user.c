/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mfile_store_fds_user.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:46:07 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/02 10:56:26 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfile.h"

t_fd	openfd(const char *filename, const char *permissions)
{
	t_manage_fds	*data;
	t_fd			new_fd;
	int				i;

	data = fd_static_storage(0);
	i = fd_indexation();
	if (!data->fds[i].n)
		return ((t_fd){0});
	data->fds[i].p = OPEN(filename, permissions);
	if (!data->fds[i].p)
	{
		data->fds[i].n = 0;
		return ((t_fd){0});
	}
	data->filenames[i] = ft_strdup(filename);
	if (!data->filenames[i])
		return (closefd(data->fds[i]), (t_fd){0});
	data->curr_fd = data->fds[i];
	data->curr_file = data->filenames[i];
	if (data->curr_fd.n > data->last)
		data->last = data->curr_fd.n;
	new_fd.n = data->fds[i].n;
	new_fd.p = data->fds[i].p;
	return (new_fd);
}

char	*get_static_buffer(int fd, bool reset, bool reset_all);

void	closefd(t_fd fd)
{
	t_manage_fds	*data;

	data = fd_static_storage(0);
	if (!data->fds[fd.n].n)
		return ;
	if (data->fds[fd.n].n == data->last)
		data->last--;
	data->fds[fd.n].n = 0;
	FREE(data->filenames[fd.n]);
	data->filenames[fd.n] = NULL;
	if (fd.p)
		CLOSE(fd.p);
	if (data->buffer[fd.n][0])
		get_static_buffer(fd.n, 1, 0);
}

/*
	Give back current data.

	Give the address of a fd and a string.
*/
int	get_filedata(t_fd *fd, char **filename)
{
	t_manage_fds	*data;

	data = fd_static_storage(0);
	if (fd)
		*fd = data->curr_fd;
	if (filename)
		*filename = data->curr_file;
	if ((fd && !fd->n) || (fd && !fd->p) || (filename && !*filename))
		return (0);
	return (1);
}

/*
	Close every fd.
	Reset the stock.
	Always safe to call.
*/
void	del_filedata(void)
{
	t_manage_fds	*data;
	int				i;

	data = fd_static_storage(0);
	i = 1;
	while ("loop as long there are fd to close")
	{
		if (i > data->last + 1)
			break ;
		if (data->fds[i].n)
			closefd(data->fds[i]);
		++i;
	}
	fd_static_storage(1);
}

/*
	Update the fd set as the current.
*/
int	switch_filedata(t_fd fd)
{
	t_manage_fds	*data;

	data = fd_static_storage(0);
	data->curr_fd = data->fds[fd.n];
	data->curr_file = data->filenames[fd.n];
	if (!data->curr_fd.n || !data->curr_fd.p || !data->curr_file)
		return (0);
	return (1);
}
