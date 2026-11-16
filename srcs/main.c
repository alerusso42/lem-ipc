/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 15:40:16 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/16 18:37:58 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-ipc.h"
#include "../includes/backend.h"
#include "../includes/frontend.h"

int	main(int argc, char **argv)
{
	t_proc	data;

	(void)argc, (void)argv;
	setup(&data);
	if (data.master == true)
		F_create(&data);
	sleep(7);
	cleanup(&data);
}
