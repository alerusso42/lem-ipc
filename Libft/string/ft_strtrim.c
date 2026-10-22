/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:27:17 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 17:52:50 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

//ANCHOR - str_trim
/*
	Trims n characters from the start index of the string object.

	@input:		[t_str *this]----->	pointer to string object
				[int32_t n]------->	number of characters to trim
	@return:	[t_str *]--------->	pointer to this
	@variables:	none
	@usage:	*-------------------------------*	
			|	str_trim(str, n);			|
			|	//OR						|
			|	trim(str, n);				|
			|	//OR						|
			|	str->m->trim(&str, n);		|
			*-------------------------------*
*/
t_str	*str_trim(t_str *this, int32_t n)
{
	if (str_check(this, NULL))
		return (_str_set_error(this, E_PARAM, "trim"));
	n += this->i;
	str_cut(this, this->i, n);
	return (this);
}
