/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_add_sign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:05:18 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 17:21:21 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

//ANCHOR - str_addr
/*
	Adds a character to the end of the string.

	@input:		[t_str *this]----->	pointer to string object
				[char c]--------->	character to add
	@return:	[t_str *]--------->	pointer to this
	@variables:	none
	@usage:	*-------------------------------*	
			|	str_addr(str, 'A');		|
			|	//OR						|
			|	add_right(str, 'A');		|
			|	//OR						|
			|	str->m->add_right(&str, 'A');|
			*-------------------------------*
*/
t_str	*str_addr(t_str *this, char c)
{
	if (str_check(this, NULL))
		return (_str_set_error(this, E_PARAM, "add_right"));
	if (this->capacity <= this->len)
		if (str_srealloc(this, 0)->err != 0)
			return (this);
	this->buff[this->len++] = c;
	this->buff[this->len] = '\0';
	return (0);
}

//ANCHOR - str_addl
/*
	Adds a character to the start of the string.

	@input:		[t_str *this]----->	pointer to string object
				[char c]--------->	character to add
	@return:	[t_str *]--------->	pointer to this
	@variables:	none
	@usage:	*-------------------------------*	
			|	str_addr(str, 'A');		|
			|	//OR						|
			|	add_right(str, 'A');		|
			|	//OR						|
			|	str->m->add_right(&str, 'A');|
			*-------------------------------*
*/
t_str	*str_addl(t_str *this, char c)
{
	int32_t	i;

	if (str_check(this, NULL) || c == '\0')
		return (_str_set_error(this, E_PARAM, "add_left"));
	if (this->capacity <= this->len)
		if (str_srealloc(this, 0)->err != 0)
			return (this);
	this->buff[this->len + 1] = '\0';
	i = this->len++;
	while (i)
	{
		this->buff[i] = this->buff[i - 1];
		i--;
	}
	this->buff[0] = c;
	return (0);
}
