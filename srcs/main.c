/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 15:40:16 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/28 13:10:57 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-ipc.h"
#include "../includes/backend.h"
#include "../includes/frontend.h"

//https://stackoverflow.com/questions/1433204/how-do-i-use-extern-to-share-variables-between-source-files
volatile int	global_sigint = false;

void	setup(t_proc *data, char **argv);

int	main(int argc, char **argv)
{
	t_proc	proc;
	t_B		back;

	(void)argc;
	setup(&proc, argv);
	if (proc.info.is_master == true && !proc.info.is_sdl_disabled)
		F_create(&proc);
	signal(SIGINT, B_sigint);
	back = (t_B){0};
	back.power_on = true;
	back.proc = &proc;
	B_timer_start(&back);
	if (proc.info.is_master == false)
		B_id_wait(&back);
	B_matchmaking(&back);
	B_setup_game(&back);
	debug_drawMap(back.proc);
	debug_drawTeams(back.proc);
	B_game_loop(&back);
	B_stop(&back);
	return (0);
}
