/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:41:16 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/27 16:15:36 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfile.h"

/*
	reset_fd reimposta read all'inizio del file, e contemporaneamente
	resetta il buffer di get_next_line.
    Se nello stock di fd era presente l'fd, lo aggiorna.
*/
int	reset_fd(t_fd fd)
{
	get_static_buffer(fd.n, 1, 0);
	return (SEEK(fd.p, 0, 0));
}
