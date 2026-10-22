/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 22:27:41 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/25 22:39:52 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

int	lst_size(t_list *lst)
{
	int	list_size;

	list_size = 0;
	if (!lst)
		return (0);
	list_size += 1;
	while ((lst->next))
	{
		lst = lst->next;
		list_size += 1;
	}
	return (list_size);
}
