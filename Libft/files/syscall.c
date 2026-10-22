/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:23:11 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/27 16:15:46 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfile.h"

int	read_curr(t_manage_fds *data, int count)
{
	char	*buff;

	buff = data->buffer[data->curr_fd.n];
	return (read(data->curr_fd.p, buff, count));
}

int	readfd(t_fd	fd, char *buff, int count)
{
	return (read(fd.p, buff, count));
}

int	writefd(t_fd fd, const char *s, size_t len)
{
	return (write(fd.p, s, len));
}
