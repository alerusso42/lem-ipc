/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 20:03:32 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 17:40:43 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

//ANCHOR - str_cpy
/*
	Copies the content of another string object or a char pointer
	into the current string object.

	@INDEX:	SET INDEX TO END OF COPIED CONTENT!
	@input:		[t_str *this]----->	pointer to string object
				[const void *other]->pointer to another string object
									or a char pointer
	@return:	[t_str *]--------->	pointer to this
	@variables:	none
	@usage:	*-------------------------------*	
			|	str_cpy(str, other);		|
			|	//OR						|
			|	cpy(str, other);			|
			|	//OR						|
			|	str->m->cpy(&str, other);	|
			*-------------------------------*
*/
t_str	*_str_cpy_char(t_str *this, const char *other)
{
	int32_t	i;
	int32_t	j;

	if (str_check(this, other))
		return (_str_set_error(this, E_PARAM, "cpy"));
	i = this->i;
	j = 0;
	while (other[j] && i < this->capacity)
	{
		this->buff[i++] = other[j++];
	}
	this->i = i;
	return (this);
}

t_str	*_str_cpy_str(t_str *this, const t_str *other)
{
	int32_t	i;
	int32_t	j;

	if (str_check(this, other))
		return (_str_set_error(this, E_PARAM, "cpy"));
	i = this->i;
	j = 0;
	while (other->buff[j] && i < this->capacity)
	{
		this->buff[i++] = other->buff[j++];
	}
	this->i = i;
	return (this);
}
