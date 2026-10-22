/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mfile.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:13:36 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/02 13:53:52 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MFILE_H
# define MFILE_H
# ifndef BUFFER_SIZE
// Memoria statica usata ---> (BUFFER_SIZE + 1) * ((MAX_FILES + 1) * 20)
#  define BUFFER_SIZE 1000
# endif
# ifndef MAX_FILES
#  define MAX_FILES 20
# endif
# include <unistd.h>
# include <string.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <malloc.h>
# include <fcntl.h>
# include <limits.h>
# include "../libft.h"

void	*free_matrix(void **matrix);
void	*free_three_d_matrix(void ***matrix);

typedef struct s_manage_fds
{
	char	buffer[MAX_FILES + 1][BUFFER_SIZE + 1];
	t_fd	fds[MAX_FILES + 1];
	char	*filenames[MAX_FILES + 1];
	t_fd	curr_fd;
	char	*curr_file;
	int		last;
}			t_manage_fds;

//		SDL_SUPPORT

t_fd			openfd(const char *filename, const char *permissions);
int				ft_open(const char *filename, const char *perm);
t_manage_fds	*fd_static_storage(bool);
int				get_filedata(t_fd *fd, char **filename);
void			del_filedata(void);
int				switch_filedata(t_fd fd);
int				fd_indexation(void);
void			closefd(t_fd fd);
int				read_curr(t_manage_fds *data, int count);
int				readfd(t_fd	fd, char *buff, int count);
char			*get_static_buffer(int fd, bool reset, bool reset_all);
char			*gnl();
int				writefd(t_fd fd, const char *s, size_t len);
int				reset_fd(t_fd fd);

#endif