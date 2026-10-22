/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:25:46 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 17:21:21 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"
#include <string.h>

static long long int	atoi_parse_result(long long int res, char sign);

int64_t	ft_atoi(const char *nptr)
{
	long long int	pow;
	long long int	res;
	int				start;
	int				i;

	res = 0;
	pow = 1;
	i = 0;
	while (ft_strchr(" \n\t\f\t\v\r", nptr[i]))
		i++;
	start = i;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	if (!ft_strchr("0123456789", nptr[i++]))
		return (LLONG_MAX);
	while (ft_strchr("0123456789", nptr[i]))
		i++;
	while (i-- != start && !ft_strchr("+-", nptr[i]))
	{
		res += (nptr[i] - '0') * pow;
		pow *= 10;
	}
	return (atoi_parse_result(res, nptr[start]));
}

//ANCHOR - str_satoi
/*
	Converts the string object's buffer to an integer.

	@input:		[t_str *str]----->	pointer to string object
				[int *n]--------->	pointer to store the result
	@return:	[string error code]
	@variables:	[int start]------->		start index for conversion
				[long long int res]->	result of conversion
	@usage:	*-------------------------------*	
			|	int n;						|
			|	if (str_satoi(str, &n) != 0)|
			|		//Handle error			|
			|	//OR						|
			|	if (str_satoi(str, &n) != 0)|
			|		//Handle error			|
			|	//OR						|
			|	str->m->satoi(str, &n);		|
			|	if (str->err != 0)			|
			|		//Handle error			|
			*-------------------------------*
*/
err		str_satoi(t_str *str, int *n)
{
	int				start;
	long long int	res;

	*n = 0;
	start = str->i;
	res = ft_atoi(str->buff + start);
	if (res == LLONG_MAX)
		return (E_ATOI_FAIL);
	*n = (int)res;
	return (E_EXIT_SUCCESS);
}

static long long int	atoi_parse_result(long long int res, char sign)
{
	if (res == 2147483648 && sign == '-')
		res = INT_MIN;
	else if (res > 2147483647)
		return (LLONG_MAX);
	else if (sign == '-')
		res = res * -1;
	return (res);
}
