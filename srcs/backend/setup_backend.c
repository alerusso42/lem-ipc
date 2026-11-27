/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_backend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 10:33:03 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/27 10:33:26 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/backend.h"

void	B_stop(t_B *backend)
{
	free(backend->arr_id);
	backend->arr_id = NULL;
	free(backend->map_copy);
	backend->map_copy = NULL;
	lst_clear(&backend->players_start_info, free);
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
