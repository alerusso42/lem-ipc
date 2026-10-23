/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02sem.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 11:17:12 by alerusso42        #+#    #+#             */
/*   Updated: 2026/10/23 12:39:24 by alerusso42       ###   ########.fr       */
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
 * 			1.	semaphore handling
 * 			2.	count number of clients using semaphores
 * 			3.	do time consuming operation using semaphores
 * 			4.	unlink file ONLY when last process is using it
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int	main(int argc, char **argv)
{
	t_shared	*shared;
	t_private	private;

	(void)argc;
	signal(SIGINT, handler_ctrl_c);
	setup(&private, argv[2]);
	shared = private.shared_ptr;
	loop(&private, shared);
	cleanup(shared);
}

static void	handler_ctrl_c(int sig)
{
	(void)sig;
	run = false;
}

static void	loop(t_private *private, t_shared *shared)
{
	int	bytes;

	while (run == true)
	{
		bytes = read(0, private->buff, BUFF_LEN - 1);
		if (bytes <= 0)
			return ;
		ft_printf("Waiting to my turn to write..\n");
		sem_wait(&shared->sem);
		ft_printf("%s: It's my turn!\n", private->name);
		ft_printf("Current buff: |%s|\n", shared->buff);
		ft_printf("Give me %d seconds..\n", time);
		ft_strlcpy(shared->buff, private->buff, bytes + 1);
		sleep(time);
		ft_printf("%s: Finish! New buff: %s\n", private->name, shared->buff);
		sem_post(&shared->sem);
	}
}
