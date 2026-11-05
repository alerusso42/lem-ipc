/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 15:40:16 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/05 20:45:11 by alerusso42       ###   ########.fr       */
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
	sleep(2);
	cleanup(&data);
}
