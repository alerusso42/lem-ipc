/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 00:16:16 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 17:21:21 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

//ANCHOR - ft_strcount
/*
	Returns the number of characters c in the string s

	@input:		[t_str *this]----->	pointer to string object
				[char c]---------->	the character to count
	@return:	[i]--------------->	number of times c has been found
	@variables:	[int count] ------>	counts the occurence of c
	@usage:	*-------------------------------*	
			|	str_count(str, c);			|
			|	//OR						|
			|	count(str, c);				|
			|	//OR						|
			|	str->m->count(&str, c);		|
			*-------------------------------*
*/
int	str_count(t_str *this, char c)
{
	if (this->err == true)
		return (0);
	return (ft_strcount(this->buff + this->i, c));
}

int	ft_strcount(const char *s, char c)
{
	int	count;

	count = 0;
	while (s)
	{
		if (*s == c)
			count++;
		++s;
	}
	return (count);
}
