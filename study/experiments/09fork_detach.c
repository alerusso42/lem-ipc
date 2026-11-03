/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09fork_detach.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 09:51:22 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/03 22:07:13 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "experiment.h"
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief this test:
 * 			OK	1.	assures that a child is detached from parent 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
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
