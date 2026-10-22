/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 19:28:04 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 17:38:01 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

//ANCHOR - _str_set_error
/*

//	!!!This function is private! It shouldn't be used!

//	Sets error state of the string object.

	@input:		[t_str *str]------>	pointer to string object
				[int err]--------->	error code
				[char *func_name]->function name where error occurred
	@return:	[t_str *]--------->	pointer to string object
	@variables:	none
*/
t_str	*_str_set_error(t_str *str, int err, char *func_name)
{
	if (str->buff == NULL)
		return (str);
	if (!str->err)
		str->err = err;
	switch (err)
	{
		case (E_ALLOC) :
			str->capacity = -1;
			err_printf("String:\tFATAL:\tAllocation error");
			break ;
		case (E_PARAM) :
			err_printf("String:\tbad parameter in function\t%s", func_name);
			break ;
		case (E_ATOI_FAIL) :
			err_printf("String:\tAtoi has failed for this param->\t");
			err_printf(func_name);
			break ;
		case (E_NPOS) :
			str->err = 0;
			break ;
	}
	err_printf("\n");
	return (str);
}

//ANCHOR - _str_check_char
/*

//	!!!This function is private! It shouldn't be used!

//	Checks validity of operations involving this object and a char pointer.

	@input:		[t_str *this]----->	pointer to string object
				[const char *other]->pointer to char
	@return:	[bool]----------->	success or failure
	@variables:	none
*/
bool	_str_check_char(t_str *this, const char *other)
{
	if (_str_check_this(this, NULL))
		return (true);
	else if (!other)
		this->err = E_PARAM;
	return (this->err > 0);
}

//ANCHOR - _str_check_str
/*

//	!!!This function is private! It shouldn't be used!

//	Checks validity of operations involving this object and a t_str pointer.

	@input:		[t_str *this]----->	pointer to string object
				[const char *other]->pointer to char
	@return:	[bool]----------->	success or failure
	@variables:	none
*/
bool	_str_check_str(t_str *this, const t_str *other)
{
	if (_str_check_this(this, NULL))
		return (true);
	else if (!other || other->err == E_ALLOC)
		this->err = E_PARAM;
	return (this->err > 0);
}

//ANCHOR - _str_check_this
/*

//	!!!This function is private! It shouldn't be used!

//	Checks validity of operations involving this object.

	@input:		[t_str *this]----->	pointer to string object
	@return:	[bool]----------->	success or failure
	@variables:	none
*/
bool	_str_check_this(t_str *this, const void *empty)
{
	(void)empty;
	if (this->i > this->len)
		this->i = this->len;
	if (this->err == E_NPOS)
		this->err = 0;
	if (this->err)
		return (this->err);
	if (!this->buff)
	{
		if (str_srealloc(this, 0)->err != 0)
		{
			this->err = E_ALLOC;
			return (true);
		}
	}
	return (this->err != 0);
}
