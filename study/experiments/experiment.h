/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   experiment.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 16:09:11 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/22 17:20:33 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPERIMENT_H
# define EXPERIMENT_H
# include "../../Libft/libft.h"
# include <sys/mman.h>
# include <sys/msg.h>
# include <sys/sem.h>
# include <sys/time.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>

# define BUFF_LEN 64
# define DEFAULT_NAME "default"
# define SHM_FILE "/lem-ipc_shared_memory"
# define SEM_FILE "/lem-ipc_sem"

typedef struct s_test
{
	char	name[BUFF_LEN];
	int		id;
}		t_test;

#endif