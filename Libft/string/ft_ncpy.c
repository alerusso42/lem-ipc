/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ncpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 20:03:32 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/24 20:24:52 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

//ANCHOR - str_ncpy
/*
	Copies up to n characters from another string object or a char pointer
	into the current string object, starting from a given index.

	@INDEX:	SET INDEX TO END OF COPIED CONTENT!
	@ALLOC:	DOES NOT REALLOC! IN CASE OF OVERFLOW, RETURNS ERROR!
	@input:		[t_str *this]----->	pointer to string object
				[const void *other]->pointer to another string object
									or a char pointer
				[int32_t start]--->	start index in other to copy from
				[int32_t n]------->	number of characters to copy
	@return:	[t_str *]--------->	pointer to this
	@variables:	none
	@usage:	*---------------------------------------*	
			|	str_ncpy(str, other, start, n);		|
			|	//OR								|
			|	ncpy(str, other, start, n);			|
			|	//OR								|
			|	str->m->ncpy(&str, other, start, n);|
			*---------------------------------------*
*/

t_str	*_str_ncpy_char(t_str *this, const char *other, int32_t strt, int32_t n)
{
	int32_t	i;
	int32_t	j;

	if (str_check(this, other) || (int32_t)ft_strlen(other) < strt || strt < 0)
		return (_str_set_error(this, E_PARAM, "find"));
	i = this->i;
	j = strt;
	while (n-- && other[j] && i < this->capacity)
	{
		this->buff[i++] = other[j++];
	}
	this->i = i;
	return (this);
}

t_str	*_str_ncpy_str(t_str *this, const t_str *other, int32_t strt, int32_t n)
{
	int32_t	i;
	int32_t	j;

	if (str_check(this, other) || other->len < strt || strt < 0)
		return (_str_set_error(this, E_PARAM, "find"));
	i = this->i;
	j = strt;
	while (n-- && other->buff[j] && i < this->capacity)
	{
		this->buff[i++] = other->buff[j++];
	}
	this->i = i;
	return (this);
}
