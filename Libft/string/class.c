/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:55:45 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 17:21:21 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

//ANCHOR - _Str_constructor
/*
	!!!This function is private! It shouldn't be used!
	To init a string stack object:
	@usage:	*-------------------------------*	
			|	STR(name, "BUFFER");		|
			|	//code ...					|
			*-------------------------------*
//REVIEW - Initialize a stack string object.
*/
t_str	_str_constructor(t_str *str, const char *buff)
{
	STR_LOG("%s\tconstructor\n", buff);
	*str = (t_str){0};
	str->capacity = -1;
	if (str_sdup(str, buff)->err != 0)
		return (*str);
	_str_set(str);
	return (*str);
}

//ANCHOR - str_new
/*
//	Initialize a heap string object.

	@input:		[t_str **str]----->	pointer to string object
				[const char *buff]->initial buffer content
	@return:	[bool]----------->	success or failure
	@variables:	none
	@usage:	*-------------------------------*	
			|	t_str *str;					|
			|	str_new(&str, "BUFFER");	|
			|	//code ...					|
			|	str_delete(&str);			|
			|	//OR, global delete needed:	|
			|	str_terminate();			|
			*-------------------------------*
*/
bool	str_new(t_str **str, const char *buff)
{
	*str = CALLOC(1, sizeof(t_str));
	if (!*str)
		return (EXIT_FAILURE);
	_str_constructor(*str, buff);
	_str_garbage_collector(*str, false);
	return (EXIT_SUCCESS);
}

//ANCHOR - _str_destructor
/*
	!!!This function is private! It shouldn't be used!

	Destructor for both stack and heap string objects.

	@input:		[void *str]----->	pointer to string object
	@return:	none
	@variables:	none
	
//REVIEW
//	If the string is heap allocated,
	it calls the garbage collector to remove it from the list
	and frees the string object itself.
*/
void	_str_destructor(void *str)
{
	STR_LOG("%s\tdestructor\n", ((t_str *)str)->buff);
	FREE(((t_str *)str)->buff);
	if (((t_str *)str)->_garbage_coll_node)
	{
		_str_garbage_collector(((t_str *)str), true);
		FREE(str);
	}
}

//ANCHOR - str_new
/*
//	Destroys all heap string objects.
	Always safe to call.

	@input:		none
	@return:	none
	@variables:	none
	@usage:	*-------------------------------*	
			|	str_terminate();			|
			*-------------------------------*
*/
void	str_terminate(void)
{
	_str_garbage_collector(NULL, true);
}

t_str	*str_print(t_str *this)
{
	return (ft_printf("%s\n", this->buff), this);
}
