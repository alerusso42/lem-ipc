/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   critical_section.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 15:42:22 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/20 08:42:11 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem-ipc.h"

//lock all semaphores
void	cr_lockAll(t_proc *proc)
{
	sem_wait(&proc->shared->s_gen);
	sem_wait(&proc->shared->s_map);
	sem_wait(&proc->shared->s_player);
	sem_wait(&proc->shared->s_print);
}

//unlock all semaphores
void	cr_unlockAll(t_proc *proc)
{
	sem_post(&proc->shared->s_print);
	sem_post(&proc->shared->s_player);
	sem_post(&proc->shared->s_map);
	sem_post(&proc->shared->s_gen);
}
