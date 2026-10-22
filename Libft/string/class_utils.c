/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 09:46:42 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 17:21:21 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

//SECTION - private

//ANCHOR - _str_reset
/*

//	!!!This function is private! It shouldn't be used!

//	Resets the string object's buffer to the given size.

	@input:		[t_str *this]----->	pointer to string object
				[int i]----------->	new buffer size
	@return:	[t_str *]--------->	pointer to string object
	@variables:	none
*/
t_str	*_str_reset(t_str *this, int i)
{
	this->capacity = -1;
	FREE(this->buff);
	this->buff = CALLOC(i + 1, sizeof(char));
	if (!this->buff)
		return (_str_set_error(this, E_ALLOC, "dup"));
	this->capacity = i;
	this->len = i;
	_str_set(this);
	return (this);
}


void	_str_set(t_str *this)
{
	this->err = 0;
	this->i = 0;
}

t_str_iterator	str_get_iterator(t_str *this)
{
	t_str_iterator	it;

	it = (t_str_iterator){0};
	it.begin = this->buff;
	it.half = this->buff + this->len / 2;
	it.end = this->buff + this->len;
	it.i = it.begin;
	return (it);
}
