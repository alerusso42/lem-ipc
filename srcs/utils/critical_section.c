/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   critical_section.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 15:42:22 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/19 15:47:17 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem-ipc.h"

int64_t	cr_int_get(sem_t *sem, int64_t *n)
{
	int64_t	copy;

	sem_wait(sem);
	copy = *n;
	sem_post(sem);
	return (copy);
}
