/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 22:40:44 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/12 19:46:43 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	lst_clear(t_list **lst, void (*del)(void *))
{
	t_list	*node_pointer;

	if (!lst)
		return ;
	while (*lst)
	{
		node_pointer = (*lst);
		(*lst) = (*lst)->next;
		lst_delone(node_pointer, *del);
	}
	lst_delone((*lst), *del);
}
