/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 20:03:32 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/24 20:24:52 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

//ANCHOR - str_excpy
/*
	Copies characters from another string object or a char pointer
	into the current string object, until a character from the given set .
	is found.

	@INDEX:	SET INDEX TO END OF COPIED CONTENT!
	@input:		[t_str *this]----->	pointer to string object
				[const void *other]->pointer to another string object
									or a char pointer
				[const void *set]-->	pointer to another string object
									or a char pointer representing the set
	@return:	[t_str *]--------->	pointer to this
	@variables:	none
	@usage:	*---------------------------------------*	
			|	str_excpy(str, other, set);		|
			|	//OR								|
			|	excpy(str, other, set);			|
			|	//OR								|
			|	str->m->incpy(&str, other, set);|
			*---------------------------------------*
*/

t_str	*_str_excpy_char_char(t_str *this, const char *other, const char *set)
{
	return (_str_scpy(this, other, set, EXCLUDE));
}

t_str	*_str_excpy_str_char(t_str *this, const t_str *other, const char *set)
{
	return (_str_scpy(this, other->buff, set, EXCLUDE));
}

t_str	*_str_excpy_char_str(t_str *this, const char *other, const t_str *set)
{
	return (_str_scpy(this, other, set->buff, EXCLUDE));
}

t_str	*_str_excpy_str_str(t_str *this, const t_str *other, const t_str *set)
{
	return (_str_scpy(this, other->buff, set->buff, EXCLUDE));
}
