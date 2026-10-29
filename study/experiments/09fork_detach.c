/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09fork_detach.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 09:51:22 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/29 09:54:57 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "experiment.h"
#include <unistd.h>
#include <stdlib.h>

int	main()
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (printf("fork failed\n"));
	if (!pid)
	{
		sleep(3);
		printf("child: ok\n");
		exit(0);
	}
	printf("parent: ok\n");
}
