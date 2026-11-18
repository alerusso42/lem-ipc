/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 16:23:19 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/18 19:06:39 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/backend.h"

void	B_setup_game()
{
	
}

void	B_stop(t_B *backend)
{
	free(backend->arr_id);
	backend->arr_id = NULL;
	cleanup(backend->proc);
}

void	B_error(t_B *backend, const char *err)
{
	backend->proc->info.error = true;
	debug_log(backend->proc, err);
	error(backend->proc, NULL);
}

void	B_sigint(int sig)
{
	(void)sig;
	global_sigint = true;	
}
