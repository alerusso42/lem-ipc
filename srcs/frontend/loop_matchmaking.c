/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_matchmaking.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 16:17:34 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/18 11:11:48 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/frontend.h"

void	F_loop_matchmaking(t_F *front)
{
	(void)front;
	ft_printf("SDL: loop matchmaking\n");
	sleep(2);
	ft_printf("SDL: end loop matchmaking\n");
}
