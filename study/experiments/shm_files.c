/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shm_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 16:08:05 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/22 17:20:49 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "experiment.h"

void	error(const char *err);

int	main(int argc, char **argv)
{
	t_test	*data;
	char	*name;
	int		fd;

	if (argc == 1)
		name = DEFAULT_NAME;
	else
		name = argv[1];
	fd = shm_open(SHM_FILE, O_CREAT | O_RDWR, 0666);
	if (fd == -1)
		error("shm_open failed");
	data = mmap(NULL, sizeof(t_test), PROT_READ | PROT_WRITE, MAP_SHARED, 3, 0);
	if (data == (void *)-1)
		error("mmap failed");
	ft_strlcpy(data->name, name, BUFF_LEN);
	usleep(4000);
	ft_printf("last name: %s\n", data->name);
	munmap(data, sizeof(t_test));
	shm_unlink(SHM_FILE);
	exit(0);
}

void	error(const char *err)
{
	perror(err);
	exit(1);
}
