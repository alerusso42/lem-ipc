/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_n.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:32:57 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/26 16:01:42 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	lst_addn(t_hlist *head, void *content, int32_t n)
{
	t_list	*lst;
	t_list	*next;
	int32_t	i;

	if (!head || n < 0)
		return (NULL);
	lst = head->p;
	i = n;
	while (i-- && lst)
		lst = lst->next;
	if (!lst)
		return ;
	next = lst->next;
	lst->next = lst_new(content);
	if (!lst->next)
	{
		head->fail = true;
		lst->next = next;
		return ;
	}
	lst->next->next = next;
}
