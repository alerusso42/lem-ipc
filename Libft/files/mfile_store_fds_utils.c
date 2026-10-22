/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mfile_store_fds_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 08:43:17 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/02 10:56:26 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfile.h"

int				fd_indexation(void);
t_manage_fds	*fd_static_storage(bool delete);

int	fd_indexation(void)
{
	t_manage_fds	*data;
	int				i;

	data = fd_static_storage(0);
	i = 1;
	while (data->fds[i].n && i != MAX_FILES)
		++i;
	if (i == MAX_FILES)
		return (0);
	data->fds[i].n = i;
	return (i);
}

t_manage_fds	*fd_static_storage(bool delete)
{
	static t_manage_fds	data;

	if (delete)
	{
		data = (t_manage_fds){0};
	}
	return (&data);
}

int	ft_open(const char *filename, const char *perm)
{
	int	mode;
	int	fd;

	if (*perm == 'r' && perm[1] == '+')
		mode = O_RDONLY | O_CREAT;	
	else if (*perm == 'r')
		mode = O_RDONLY;
	else if (*perm == 'w' && perm[1] == '+')
		mode = O_RDWR | O_TRUNC | O_CREAT;
	else if (*perm == 'w')
		mode = O_WRONLY | O_TRUNC;
	else if (*perm == 'a' && perm[1] == '+')
		mode = O_RDWR | O_APPEND | O_CREAT;
	else if (*perm == 'a')
		mode = O_RDWR | O_APPEND;
	else
		return (err_printf("ft_open: flag %s is not allowed.\n", perm));
	if (mode & O_CREAT)
		fd = open(filename, mode, 0777);
	else
		fd = open(filename, mode);
	if (fd == -1)
		return (0);
	return (fd);
}

/*
#define POKEDEX "../../../../getnextline/updated_pokedex.txt"
#define TEST "../tests/long.txt"
#include <unistd.h>
#include <malloc.h>
#include <fcntl.h>
int main()
{
	t_fd	fd1 = openfd(POKEDEX, "r");
	t_fd	fd2 = openfd(TEST, "a+");
	char *s = NULL;
	int size = SDL_RWsize(fd1.p);
	s = malloc(size + 1);
	size = READ(fd1.p, s, sizeof(char), size);
	s[size] = 0;
	char	*tmp = memchr(s, 'G', size);
	WRITE(fd2.p, tmp, sizeof(char), 40);
    free(s);
	t_fd	fd;
	get_filedata(&fd, &s);
	switch_filedata(fd1);
	get_filedata(&fd, &s);
	switch_filedata(fd2);
	get_filedata(&fd, &s);
	del_filedata();
	return (0);
}
*/
