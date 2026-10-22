/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 22:52:27 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 17:50:42 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

static t_str	*no_realloc(t_str *s, const char *s2, int32_t n, int32_t len);

t_str *_str_join_str(t_str *s, const t_str *s2, int32_t n)
{
	int32_t i;
	char   *new_s;

	if (str_check(s, s2) || n < 0 || n > s2->len)
		return (_str_set_error(s, E_PARAM, "join"));
	if (s->capacity > s->len + s2->len)
		return (no_realloc(s, s2->buff, n, s->len));
	i = s->len + s2->len - n;
	new_s = CALLOC(i + 1, sizeof(char));
	if (!new_s)
		return (_str_set_error(s, E_ALLOC, NULL));
	ft_strlcpy(new_s, s->buff, s->i + 1);
	ft_strlcpy(new_s + s->i, s2->buff + n, INT_MAX);
	if (s->buff[s->i])
		ft_strlcpy(new_s + s->i + s2->len - n, s->buff + s->i, INT_MAX);
	FREE(s->buff);
	s->buff = new_s;
	s->capacity = i;
	s->len = i;
	s->i += s2->len - n;
	return (s);
}

t_str *_str_join_char(t_str *s, const char *s2, int32_t n)
{
	int32_t i;
	int32_t len;
	char   *new_s;

	if (str_check(s, s2) || n < 0)
		return (_str_set_error(s, E_PARAM, "join"));
	len = ft_strlen(s2);
	if (len < n)
		return (_str_set_error(s, E_PARAM, "join"));
	if (s->capacity > s->len + len)
		return (no_realloc(s, s2, n, len));
	i = s->len + len - n;
	new_s = CALLOC(i + 1, sizeof(char));
	if (!new_s)
		return (_str_set_error(s, E_ALLOC, "join"));
	ft_strlcpy(new_s, s->buff, s->i + 1);
	ft_strlcpy(new_s + s->i, s2 + n, INT_MAX);
	if (s->buff[s->i])
		ft_strlcpy(new_s + s->i + len - n, s->buff + s->i, INT_MAX);
	FREE(s->buff);
	s->buff = new_s;
	s->len = i;
	s->capacity = i;
	s->i += len - n;
	return (s);
}

static t_str	*no_realloc(t_str *s, const char *s2, int32_t n, int32_t len)
{
	int32_t	other_len;

	other_len = len - n;
	for (int32_t i = s->len; i != s->i; i--)
		s->buff[i + other_len] = s->buff[i];
	ft_strlcpy(s->buff + s->i, s2 + n, other_len + 1);
	s->len += other_len;
	s->i += other_len;
	return (s);
}
