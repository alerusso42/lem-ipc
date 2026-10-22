/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uplowcase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:00:26 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 17:21:21 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

void	ft_tolower(char *str)
{
	while (str && *str)
	{
		*str += ((*str >= 'A' && *str <= 'Z') * 32);
		str++;
	}
}

void	ft_toupper(char *str)
{
	while (str && *str)
	{
		*str -= ((*str >= 'a' && *str <= 'z') * 32);
		str++;
	}
}

//ANCHOR - str_lower
/*
	Converts all characters in the string to lowercase.

	@input:		[t_str *str]----->	pointer to string object
	@return:	[t_str *]--------->	pointer to this
	@variables:	none
	@usage:	*-------------------------------*	
			|	str_lower(str);			|
			|	//OR						|
			|	lower(str);				|
			|	//OR						|
			|	str->m->lower(&str);	|
			*-------------------------------*
*/
t_str	*str_lower(t_str *str)
{
	if (str_check(str, NULL))
		return (_str_set_error(str, E_PARAM, "str_lower"));
	ft_tolower(str->buff + str->i);
	return (str);
}

//ANCHOR - str_lower
/*
	Converts all characters in the string to lowercase.

	@input:		[t_str *str]----->	pointer to string object
	@return:	[t_str *]--------->	pointer to this
	@variables:	none
	@usage:	*-------------------------------*	
			|	str_lower(str);			|
			|	//OR						|
			|	lower(str);				|
			|	//OR						|
			|	str->m->lower(&str);	|
			*-------------------------------*
*/
t_str	*str_upper(t_str *str)
{
	if (str_check(str, NULL))
		return (_str_set_error(str, E_PARAM, "str_upper"));
	ft_toupper(str->buff + str->i);
	return (str);
}

/*
int	main(void)
{
	char     *str1 = "";
	char    str2[12] = "KONO DIO DA";
	char    str3[40] = "SPAZIO PER EVENTUALI PROVE";

	ft_strlowcase(str1);
	printf("Empty case: %s", str1);
    //str[15] = "kono dio da";
	ft_strlowcase(str2);
	printf("\nRight case: %s", str2);
    //str[15] = "spazio per eventuali prove del correttore";
	ft_strlowcase(str3);
	printf("\nTest: %s", str3);
	return (0);
}*/
