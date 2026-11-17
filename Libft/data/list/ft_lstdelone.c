/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_delone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 22:40:30 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/12 19:46:52 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

/**
 * @brief delete current node. Ptr will:

 * 		1)	point to next node, if exists;
 * 
 * 		2)	point to prev node, if exists;
 * 
 * 		3)	reset to NULL.

 * @param lst ptr to node
 * @param del (void (*)(void *)) function to free data
 */
void	lst_delone(t_list **lst, void (*del)(void *))
{
	t_list	*prev;
	t_list	*next;

	if (!lst)
		return ;
	prev = (*lst)->prev;
	next = (*lst)->next;
	if (del)
		del((*lst)->content);
	if (next)
		next->prev = prev;
	if (prev)
		prev->next = next;
	FREE((*lst));
	if (next)
		*lst = next;
	else
		*lst = prev;
}

void	lst2_delone(t_list2 *lst, void (*del)(void *))
{
	if (del)
	{
		del(lst->content1);
		del(lst->content2);
	}
	FREE(lst);
}
