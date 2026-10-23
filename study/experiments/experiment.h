/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   experiment.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 16:09:11 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/23 12:38:02 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPERIMENT_H
# define EXPERIMENT_H
# include "../../Libft/libft.h"
# include <sys/mman.h>
# include <sys/msg.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>

# define BUFF_LEN 64
# define DEFAULT_NAME "default"
# define SHM_FILE "/lem-ipc_shared_memory"
# define SEM_FILE "/lem-ipc_sem"

typedef struct s_shared
{
	char	buff[BUFF_LEN];
	sem_t	sem;
	int		id;
	int		n_client;
}		t_shared;

typedef struct s_private
{
	char		buff[BUFF_LEN];
	t_shared	*shared_ptr;
	const char	*name;
	bool		master;
}		t_private;

void	setup(t_private *data, const char *name);
void	error(const char *err);
void	cleanup(t_shared *data);

#endif