/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 22:43:14 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 17:40:43 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

t_str	*str_srealloc(t_str *this, int32_t n)
{
	char	*temp;
	int		i;

	if (n <= 0)
		n = this->capacity + _STR_REALLOC_SIZE;
	temp = this->buff;
	this->buff = CALLOC(n + 1, sizeof(char));
	if (!this->buff)
		return (_str_set_error(this, E_ALLOC, "_realloc"));
	this->capacity = n;
	if (!temp)
		return (_str_set(this), this);
	i = this->i;
	if (this->i > n)
		i = n;
	str_ncpy(this, temp, 0, this->len);
	this->i = i;
	FREE(temp);
	this->buff[this->len] = 0;
	return (this);
}

//ANCHOR - str_delete
/*
	Deletes the string object and frees its memory.

	@input:		[t_str *this]----->	pointer to string object
	@return:	[t_str *]--------->	NULL
	@variables:	none
	@usage:	*-------------------------------*	
			|	str = str_delete(str);		|
			|	//OR						|
			|	str = delete(str);			|
			|	//OR						|
			|	str = str->m->delete(&str);	|
			*-------------------------------*

//NOTE - WARNING
	This function frees the string object and returns NULL.
	If you access the string object after calling this function,
	it will lead to undefined behavior.
*/
t_str	*_str_delete(t_str *this)
{
	if (!this)
		return (NULL);
	if (this->_garbage_coll_node)
		return (lst_delone(this->_garbage_coll_node, _str_destructor), NULL);
	FREE(this->buff);
	this->buff = NULL;
	this->capacity = -1;
	
	return (NULL);
}
