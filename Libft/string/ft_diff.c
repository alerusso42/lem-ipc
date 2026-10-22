/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_diff.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:53:25 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 17:40:43 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

//ANCHOR - str_diff
/*
	Advances the index of the string object while the current character
	does not belong to the given string or char pointer.

	@input:		[t_str *this]----->	pointer to string object
				[const void *other]->pointer to another string object
									or a char pointer
	@return:	[t_str *]--------->	pointer to this
	@variables:	none
	@usage:	*-------------------------------*	
			|	str_diff(str, other);		|
			|	//OR						|
			|	diff(str, other);			|
			|	//OR						|
			|	str->m->diff(&str, other);	|
			*-------------------------------*
*/
t_str	*_str_diff_chr(t_str *this, char other)
{
	char	chr[2];

	if (str_check(this, NULL))
		return (_str_set_error(this, E_PARAM, "find"));
	*chr = other;
	this->i = sub_strlen(this->buff + this->i, chr, INCLUDE);
	return (this);
}

t_str	*_str_diff_char(t_str *this, const char *other)
{
	if (str_check(this, NULL))
		return (_str_set_error(this, E_PARAM, "find"));
	this->i = sub_strlen(this->buff + this->i, other, INCLUDE);
	return (this);
}

t_str	*_str_diff_str(t_str *this, const t_str *other)
{
	if (str_check(this, NULL))
		return (_str_set_error(this, E_PARAM, "find"));
	this->i = sub_strlen(this->buff + this->i, other->buff, INCLUDE);
	return (this);
}
