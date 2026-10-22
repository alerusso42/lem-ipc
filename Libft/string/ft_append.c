/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 08:47:34 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 17:50:59 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

//	Uses str_join under the hood.
t_str	*_str_app_str(t_str *s, const t_str *s2)
{
	int32_t	temp;

	if (!s || s->i == STRING_NPOS)
		return (s);
	temp = s->i;
	s->i = 0;
	_str_join_str(s, s2, 0);
	if (s->i != STRING_NPOS)
		s->i = temp;
	return (s);
}

//	Uses str_join under the hood.
t_str	*_str_app_char(t_str *s, const char *s2)
{
	int32_t	temp;

	if (!s || s->i == STRING_NPOS)
		return (s);
	temp = s->i;
	s->i = 0;
	_str_join_char(s, s2, 0);
	if (s->i != STRING_NPOS)
		s->i = temp;
	return (s);
}
