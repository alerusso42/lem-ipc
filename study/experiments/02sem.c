/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02sem.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 11:17:12 by alerusso42        #+#    #+#             */
/*   Updated: 2026/10/23 13:50:23 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "experiment.h"

static void	handler_ctrl_c(int sig);
static void	loop(t_private *private, t_shared *shared);

//	goal:	program that uses shared resource concurrently

bool		run = true;
const int	time = 5;

/**
 * @brief this test:
 * 			OK	1.	semaphore handling
 * 			OK	2.	count number of clients using semaphores
 * 			OK	3.	do time consuming operation using semaphores
 * 			OK	4.	unlink file ONLY when last process is using it
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int	main(int argc, char **argv)
{
	t_shared	*shared;
	t_private	private;

	signal(SIGINT, handler_ctrl_c);
	setup(&private, argc > 1 ? argv[1] : NULL);
	shared = private.shared_ptr;
	loop(&private, shared);
	cleanup(shared);
}

static void	handler_ctrl_c(int sig)
{
	(void)sig;
	run = false;
	close(0);
}

static void	loop(t_private *private, t_shared *shared)
{
	int	bytes;

	while (run == true)
	{
		ft_printf("$G%s$Z: I am reading!\n", private->name);
		bytes = read(0, private->buff, BUFF_LEN - 1);
		if (bytes <= 0 || run == false)
			return ;
		ft_printf("$G%s$Z: Waiting to my turn to write..\n", private->name);
		sem_wait(&shared->sem);
		ft_printf("$G%s$Z: It's my turn!\n", private->name);
		ft_printf("Current buff: |%s|\n", shared->buff);
		ft_printf("Give me %d seconds..\n", time);
		ft_strlcpy(shared->buff, private->buff, bytes + 1);
		sleep(time);
		ft_printf("$G%s$Z: Finish! New buff: %s\n", private->name, shared->buff);
		sem_post(&shared->sem);
	}
}
