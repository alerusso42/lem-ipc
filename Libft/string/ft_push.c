/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 08:47:34 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 17:51:38 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

t_str	*_str_push_str(t_str *s, const t_str *s2)
{
	int32_t	temp;

	if (str_check(s, s2) != 0)
		return (_str_set_error(s, E_PARAM, "push"));
	temp = s->i;
	s->i = s->len;
	_str_join_str(s, s2, 0);
	if (s->i != STRING_NPOS)
		s->i = temp;
	return (s);
}

t_str	*_str_push_char(t_str *s, const char *s2)
{
	int32_t	temp;

	if (str_check(s, s2) != 0)
		return (_str_set_error(s, E_PARAM, "push"));
	temp = s->i;
	s->i = s->len;
	_str_join_char(s, s2, 0);
	if (s->i != STRING_NPOS)
		s->i = temp;
	return (s);
}

t_str	*_str_push_chr(t_str *s, char c)
{
	int32_t	temp;
	char	other[2];

	if (str_check(s, NULL) != 0)
		return (_str_set_error(s, E_PARAM, "push"));
	temp = s->i;
	s->i = s->len;
	other[0] = c;
	other[1] = '\0';
	_str_join_char(s, other, 0);
	if (s->i != STRING_NPOS)
		s->i = temp;
	return (s);
}
