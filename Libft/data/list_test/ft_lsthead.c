/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsthead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:02:00 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/26 16:45:00 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	_head_upd(t_hlist *head, int32_t variation, void *last)
{
	if (!head || !variation)
		return ;
	if (last)
		((t_list2 *)head->last)->next = last;
	head->len += variation;
	if (head->len == 0)
	{
		*head = (t_hlist){0};
		return ;
	}
	if (head->len % 2)
		head->half = ((t_list *)head->half)->next;
}
