/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01shm_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 16:08:05 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/23 12:28:03 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "experiment.h"

void	_error(const char *err);
void	_cleanup(int fd, t_shared *data);

//	goal:	share the memory without leaks

/**
 * @brief this test:
 * 			OK-	1.	how to open a shared file
 * 			OK-	2.	how to mmap its memory
 * 			OK-	3.	how to cleanup the memory
 * 			OK-	4.	the need to resize it (man shm_open)
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int	main(int argc, char **argv)
{
	t_shared	*data;
	char		*name;
	int			fd;

	if (argc == 1)
		name = DEFAULT_NAME;
	else
		name = argv[1];
	ft_printf("Check file: %d\n", access("/dev/shm" SHM_FILE, F_OK));
	fd = shm_open(SHM_FILE, O_RDWR | O_CREAT, 0666);
	if (fd == -1)
		_error("shm_open failed");
	data = mmap(NULL, sizeof(t_shared), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (data == (void *)-1)
		return (_cleanup(fd, data), _error("mmap failed"), 1);
	if (ftruncate(fd, sizeof(t_shared)) != 0)
		return (_cleanup(fd, data), _error("ftruncate failed"), 1);
	close(fd);
	*data = (t_shared){0};
	ft_strlcpy(data->buff, name, BUFF_LEN);
	usleep(4000000);
	ft_printf("last name: %s\n", data->buff);
	_cleanup(fd, data);
}

void	_error(const char *err)
{
	perror(err);
	exit(1);
}

void	_cleanup(int fd, t_shared *data)
{
	if (fd != -1)
	{
		close(fd);
		shm_unlink(SHM_FILE);
	}
	if (data != (void *)-1)
		munmap(data, sizeof(t_shared));
}
