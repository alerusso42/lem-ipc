/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 15:40:16 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/14 20:03:22 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-ipc.h"
#include "../includes/setup.h"
#include "../includes/frontend.h"

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argc, (void)argv;
	setup(&data);
	if (data.master == true)
		F_create(&data);
	data.msg.mtype = 1;
	data.msg.buff[0] = MSGE_CLIENT_NEW;
	msgsnd(data.msg_fd, &data.msg, BUFF_LEN, O_NONBLOCK);
	sleep(5);
	data.msg.buff[0] = MSGE_CLIENT_DEL;
	msgsnd(data.msg_fd, &data.msg, BUFF_LEN, O_NONBLOCK);
	sleep(5);
	cleanup(&data);
}
