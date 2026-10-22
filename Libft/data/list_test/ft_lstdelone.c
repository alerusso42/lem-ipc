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

void	lst_delone(t_list *lst, void (*del)(void *))
{
	if (del)
		del(lst->content);
	FREE(lst);
}

void	lst_del(t_list *lst, void (*del)(void *))
{
	t_list	*next;
	t_list	*prev;

	if (!lst)
		return ;
	prev = lst->prev;
	next = lst->next;
	if (del)
		del(lst->content);
	FREE(lst);
	if (prev)
		prev->next = next;
}
