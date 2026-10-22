/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_find.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:44:16 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 17:40:43 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

int32_t	ft_strrstr_int(const char *, const char *);

t_str	*_str_rfind_chr(t_str *this, char other)
{
	char	chr[2];

	if (str_check(this, NULL))
		return (_str_set_error(this, E_PARAM, "rfind"));
	*chr = other;
	chr[1] = 0;
	this->i = ft_strrstr_int(this->buff, chr);
	return (this);
}

t_str	*_str_rfind_char(t_str *this, const char *other)
{
	if (str_check(this, NULL))
		return (_str_set_error(this, E_PARAM, "rfind"));
	this->i = ft_strrstr_int(this->buff, other);
	return (this);
}

t_str	*_str_rfind_str(t_str *this, const t_str *other)
{
	if (str_check(this, NULL))
		return (_str_set_error(this, E_PARAM, "rfind"));
	this->i = ft_strrstr_int(this->buff, other->buff);
	return (this);
}
