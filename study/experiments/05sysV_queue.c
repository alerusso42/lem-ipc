/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05sysV_queue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 23:16:40 by codespace         #+#    #+#             */
/*   Updated: 2026/10/26 12:31:43 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "experiment.h"

static void	init_msgq(t_shared *shared, t_private *private);
static void	handler_ctrl_c(int sig);
static void	loop(t_shared *shared, t_private *private);
static int	msg_room(t_shared *shared, t_private *private, t_msg *msg);

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
	close(private.msg_fd);
	sem_wait(&shared->sem);
	if (shared->n_client == 1)
	{
		if (msgctl(private.msg_fd, IPC_RMID, NULL) != 0)
			perror("msgctl, IPC_RMID");
		else
			ft_printf("$Y Queue completely DEMOLISHED.\n$Z");
	}
	sem_post(&shared->sem);
	cleanup(shared);
}

static void	init_msgq(t_shared *shared, t_private *private)
{
	struct msqid_ds	ds;
	key_t			key;

	key = ftok(MSQ_FILE, 42);
	if (key < 0)
		return (cleanup(shared), error("ftok"));
	private->msg_fd = msgget(key, IPC_CREAT | 0666);
	if (private->msg_fd < 0)
		return (cleanup(shared), error("msgget"));
	ds = (struct msqid_ds){0};
	ds.msg_perm.mode = 0666;
	ds.msg_perm.cuid = getuid();
	ds.msg_perm.gid = getgid();
	ds.msg_qbytes = 100000;
	(void)ds;
}

static void	handler_ctrl_c(int sig)
{
	(void)sig;
	run = false;
	close(0);
}

static void	loop(t_shared *shared, t_private *private)
{
	int		bytes;
	int		n_client;
	t_msg	msg;

	msg.mtype = 1;
	private->msg_type = private->id;
	msg = (t_msg){0};
	while (run == true)
	{
		ft_printf("==Please write something to your friends==\n");
		bytes = read(0, msg.buff, BUFF_LEN - 1);
		if (bytes <= 0)
			return ;
		msg.buff[bytes] = 0;
		n_client = msg_room(shared, private, &msg);
		ft_printf("$G%s$Z: msgsnd to %d clients: |%s|\n", private->name, n_client, msg.buff);
		ft_printf("$G%s$Z: msgrecv messages:\n", private->name);
		while (msgrcv(private->msg_fd, private, BUFF_LEN, private->id, IPC_NOWAIT) > 0)
			ft_printf("====> |%s|\n", private->buff);
		sleep(1);
	}
}

static int	msg_room(t_shared *shared, t_private *private, t_msg *msg)
{
	int			n_client;
	static char	tmp[BUFF_LEN];

	sem_wait(&shared->sem);
	n_client = shared->n_client + 1;	
	sem_post(&shared->sem);
	sub_strcpy(tmp, msg->buff, "\n", EXCLUDE);
	sub_strcpy(msg->buff, private->name, "", EXCLUDE);
	sub_strcpy(msg->buff + private->name_len, ":\t", "", EXCLUDE);
	ft_strlcpy(msg->buff + private->name_len + 2, tmp, BUFF_LEN - private->name_len - 2);
	for (int i = 1; i != n_client; i++)
	{
		if (i == private->id)
			continue ;
		msg->mtype = i;
		if (msgsnd(private->msg_fd, msg, BUFF_LEN, IPC_NOWAIT) == -1)
			return ((void)perror("msgsnd failed"), -42);
	}
	return (n_client - 2);
}
