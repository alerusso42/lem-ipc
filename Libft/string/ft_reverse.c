/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:26:34 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 17:21:21 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

void	ft_rev_int(int *tab, int size)
{
	int	i;
	int	t;

	i = 0;
	while (i < size / 2)
	{
		t = tab[i];
		tab[i] = tab[size - 1 - i];
		tab[size - 1 - i] = t;
		i++;
	}
}

void	ft_rev_str(char *arr)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	j = 0;
	while (arr[j] != '\0')
		++j;
	--j;
//	if (arr[0] == '-')
//		++i;
	while (i < j)
	{
		temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
		++i;
		--j;
	}
}

//ANCHOR - str_reverse
/*
	Reverses the content of the string object's buffer.

	@input:		[t_str *str]----->	pointer to string object
	@return:	[t_str *]--------->	pointer to this
	@variables:	[int i]----------->	start index
				[int j]----------->	end index
				[char t]---------->	temporary char for swapping
	@usage:	*-------------------------------*	
			|	str_reverse(str);			|
			|	//OR						|
			|	reverse(str);				|
			|	//OR						|
			|	str->m->reverse(&str);		|
			*-------------------------------*
*/
t_str	*str_reverse(t_str *str)
{
	int		i;
	int		j;
	char	t;

	if (str_check(str, NULL))
		return (_str_set_error(str, E_PARAM, "reverse"));
	i = 0;
	j = str->len - 1;
	while (i < j)
	{
		t = str->buff[i];
		str->buff[i] = str->buff[j];
		str->buff[j] = t;
		++i;
		--j;
	}
	return (str);
}
