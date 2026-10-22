/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:33:36 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 17:21:21 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

size_t	ft_strlen(const char *s)
{
	size_t	strlen;

	strlen = 0;
	while ((*s++ != '\0'))
		++strlen;
	return (strlen);
}

int	str_get_len(t_str *str)
{
	if (str->len)
		return (str->len);
	return (ft_strlen(str->buff));
}
