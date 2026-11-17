/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 15:40:16 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/17 13:14:01 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-ipc.h"
#include "../includes/backend.h"
#include "../includes/frontend.h"

void	setup(t_proc *data, char **argv);

int	main(int argc, char **argv)
{
	t_proc	proc;

	(void)argc;
	setup(&proc, argv);
	if (proc.info.is_master == true && !proc.info.is_sdl_disabled)
		F_create(&proc);
	sleep(7);
	cleanup(&proc);
}
