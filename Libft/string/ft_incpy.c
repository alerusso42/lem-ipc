/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_incpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 20:03:32 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/24 20:24:52 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

//ANCHOR - str_incpy
/*
	Copies characters from another string object or a char pointer
	into the current string object, while characters belong to the given set.

	@INDEX:	SET INDEX TO END OF COPIED CONTENT!
	@input:		[t_str *this]----->	pointer to string object
				[const void *other]->pointer to another string object
									or a char pointer
				[const void *set]-->	pointer to another string object
									or a char pointer representing the set
	@return:	[t_str *]--------->	pointer to this
	@variables:	none
	@usage:	*---------------------------------------*	
			|	str_incpy(str, other, set);		|
			|	//OR								|
			|	incpy(str, other, set);			|
			|	//OR								|
			|	str->m->incpy(&str, other, set);|
			*---------------------------------------*
*/

t_str	*_str_scpy(t_str *this, const char *other, const char *set, int m)
{
	int32_t	len;

	len = (int32_t)ft_strlen(other);
	if (str_check(this, other) || !set)
		return (_str_set_error(this, E_PARAM, "scpy"));
	if (len > this->capacity - this->i)
		if (str_srealloc(this, len + _STR_REALLOC_SIZE)->err != 0)
			return (_str_set_error(this, E_ALLOC, "scpy"));
	len = sub_strcpy(this->buff + this->i, other, set, m);
	this->len += len;
	this->i += len;
	return (this);
}

t_str	*_str_incpy_char_char(t_str *this, const char *other, const char *set)
{
	return (_str_scpy(this, other, set, INCLUDE));
}

t_str	*_str_incpy_str_char(t_str *this, const t_str *other, const char *set)
{
	return (_str_scpy(this, other->buff, set, INCLUDE));
}

t_str	*_str_incpy_char_str(t_str *this, const char *other, const t_str *set)
{
	return (_str_scpy(this, other, set->buff, INCLUDE));
}

t_str	*_str_incpy_str_str(t_str *this, const t_str *other, const t_str *set)
{
	return (_str_scpy(this, other->buff, set->buff, INCLUDE));
}
