/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:50:37 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 17:50:28 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return ((s1 > s2) - (s1 < s2));
	while (*s1 && *s2 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	if (!*s2)
		return (0);
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}

int32_t	_str_cmp_char(t_str *this, const char *other)
{
	register int32_t	n1;

	if (str_check(this, NULL))
		return (_str_set_error(this, E_PARAM, "cmp"), 0);
	n1 = this->i;
	while (this->buff[n1] && *other && this->buff[n1] == *other)
	{
		++n1;
		++other;
	}
	return ((uint8_t)(this->buff[n1]) - (uint8_t)(*other));
}

int32_t	_str_cmp_str(t_str *this, const t_str *other)
{
	register int32_t	n1;
	register int32_t	n2;

	if (str_check(this, NULL))
		return (_str_set_error(this, E_PARAM, "cmp"), 0);
	n1 = this->i;
	n2 = other->i;
	while (this->buff[n1] && other->buff[n2] \
		&& this->buff[n1] == other->buff[n2])
	{
		++n1;
		++n2;
	}
	return ((uint8_t)(this->buff[n1]) - (uint8_t)(other->buff[n2]));
}
