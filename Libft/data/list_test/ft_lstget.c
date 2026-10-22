/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:33:02 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/26 15:51:14 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	*lst_get(t_list *lst, int32_t n)
{
	if (!lst || n < 0)
		return (NULL);
	while (n-- && lst)
		lst = lst->next;
	return (lst);
}
