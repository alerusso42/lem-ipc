/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03extend_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 14:17:36 by alerusso42        #+#    #+#             */
/*   Updated: 2026/10/23 15:43:45 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "experiment.h"

//	goal:	extend mmap memory runtime

void	test_mem(void *ptr, int size, const char *text);
void	fill_mem(void *ptr, int size);

/**
 * @brief this test:
 * 			1.	fill memory and check there is everything
 * 			2.	extend memory and check there is still everything
 * 			3.	fill new memory and test it
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int	main(int argc, char **argv)
{
	t_shared	*shared;
	t_private	private;
	int			size;
	int			fd;

	(void)fd;
	setup(&private, argc > 1 ? argv[1] : NULL);
	shared = private.shared_ptr;
	size = sizeof(t_shared);
	fill_mem(shared, BUFF_LEN);
	test_mem(shared, BUFF_LEN, "test with regular memory");
	munmap(shared, sizeof(t_shared));
	fd = shm_open(SHM_FILE, O_RDWR | O_CREAT, 0666);
	shared = mmap(NULL, size * 2, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (shared == (void *)-1)
		return (close(fd), error("mmap"), cleanup(shared), 1);
	if (ftruncate(fd, size * 2) != 0)
		return (error("ftruncate"), cleanup(shared), 1);
	close(fd);
	test_mem(shared, BUFF_LEN, "test with extended memory");
	fill_mem(((void *)shared) + size, BUFF_LEN);
	test_mem(((void *)shared) + size, BUFF_LEN, "test with new memory");
	cleanup(shared);
}

void	fill_mem(void *ptr, int size)
{
	for (int i = 0; i != size; i++)
	{
		// ft_printf("%d ", i);
		((char *)ptr)[i] = i % 256;		
	}
}

void	test_mem(void *ptr, int size, const char *text)
{
	ft_printf("%s:\t", text);
	for (int i = 0; i != size; i++)
	{
		if (((char *)ptr)[i] != i % 256)
			return ((void)ft_printf("$RKO$Z at %d\n", i));
	}
	ft_printf("$GOK$Z\n");	
}
