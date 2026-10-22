/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:35:18 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/26 16:40:52 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_hlist	*lst_init(void *content)
{
	t_hlist	*init;

	init = ft_calloc(1, sizeof(t_hlist));
	if (!init)
		return (NULL);
	init->p = lst_new(content);
	if (!init->p)
		return (FREE(init), NULL);
	init->last = init->p;
	init->half = init->p;
	init->len = 1;
	return (init);
}
