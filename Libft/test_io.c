/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:23:59 by codespace         #+#    #+#             */
/*   Updated: 2025/11/27 17:21:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "files/mfile.h"

//  clear;cc -Wall -Wextra -Werror -g ./test_io.c data/list/*.c mem/*.c string/*.c printf/*.c files/*.c

//NOTE - test main
#define TEST "test.c"

int	main(void)
{
	char	*line;
	t_fd	fd;

	fd = openfd(TEST, "r");
	if (fd.n == 0)
	{
		ft_printf(2, "Error opening file\n");
		return (1);
	}
	line = gnl();
	int c = 1;
	while (line != NULL)
	{
		printf("%s\n", line);
		FREE(line);
		line = gnl();
		c++;
	}
	(void)c;
	del_filedata();
	return (0);
}
