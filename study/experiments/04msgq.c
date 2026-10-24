/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04msgq.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 10:23:23 by alerusso42        #+#    #+#             */
/*   Updated: 2026/10/24 10:35:40 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "experiment.h"

static void	handler_ctrl_c(int sig);
static void	loop(t_shared *shared, t_private *private);

int	run = true;

int	main(int argc, char **argv)
{
	t_shared	*shared;
	t_private	private;

	signal(SIGINT, handler_ctrl_c);
	setup(&private, argc > 1 ? argv[1] : NULL);
	shared = private.shared_ptr;
	loop(shared, &private);
	cleanup(shared);
}

static void	handler_ctrl_c(int sig)
{
	(void)sig;
	run = false;
	close(0);
}

static void	loop(t_shared *shared, t_private *private)
{
	while (run == true)
	{
		
	}
}
