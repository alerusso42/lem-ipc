/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04mqueue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 10:23:23 by alerusso42        #+#    #+#             */
/*   Updated: 2026/10/24 23:14:46 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "experiment.h"

static void	init_msgq(t_shared *shared, t_private *private);
static void	handler_ctrl_c(int sig);
static void	loop(t_shared *shared, t_private *private);

int	run = true;

/**
 * @brief this test:
 * 			OK	1.	send message to a queue
 * 			OK	2.	display them	
 * 			OK	3.	check if a client can see its own messages (yes....)
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
	init_msgq(shared, &private);
	loop(shared, &private);
	mq_close(private.mq_fd);
	cleanup(shared);
}

static void	init_msgq(t_shared *shared, t_private *private)
{
	private->mq_info.mq_maxmsg = 5;
	private->mq_info.mq_msgsize = BUFF_LEN;
	private->mq_fd = mq_open(MSQ_FILE, O_CREAT | O_RDWR, 0666, &private->mq_info);
	if (private->mq_fd < 0)
		return (cleanup(shared), error("mq_open"));
}

static void	handler_ctrl_c(int sig)
{
	(void)sig;
	run = false;
	close(0);
}

static void	loop(t_shared *shared, t_private *private)
{
	int	bytes;

	while (run == true)
	{
		bytes = read(0, private->buff, BUFF_LEN - 1);
		if (bytes <= 0)
			return ;
		sem_wait(&shared->sem);
		ft_printf("$G%s$Z: Old buffer:\t%s\n", private->name, shared->buff);
		ft_strlcpy(shared->buff, private->buff, bytes);
		ft_printf("$G%s$Z: New buffer:\t%s\n", private->name, shared->buff);
		if (mq_getattr(private->mq_fd, &private->mq_info) != 0)
			return (sem_post(&shared->sem), (void)perror("mq_getatr failed\n"));
		if (private->mq_info.mq_curmsgs)
		{
			mq_receive(private->mq_fd, private->buff, BUFF_LEN, &private->mq_priority);
			if (errno)
				return (sem_post(&shared->sem), (void)perror("mq_receive failed\n"));
			ft_printf("$G%s$Z: mq_receive buffer:\t%s\n", private->name, private->buff);
		}
		mq_send(private->mq_fd, shared->buff, BUFF_LEN, rand() % 5);
		if (errno)
			return (sem_post(&shared->sem), (void)perror("mq_receive failed\n"));
		sem_post(&shared->sem);
		sleep(1);
	}
}
