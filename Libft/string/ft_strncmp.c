/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:47:19 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 17:41:53 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

//ANCHOR - str_ncmp
/*
	Compares up to n characters of the string object's buffer
	with another string object or a char pointer.

	@input:		[t_str *this]----->	pointer to string object
				[const void *other]->pointer to another string object
									or a char pointer
				[int32_t n]------->	number of characters to compare
	@return:	[int32_t]------->	result of comparison
	@variables:	none
	@usage:	*-------------------------------------------*	
			|	int res = str_ncmp(str, other, n);		|
			|	//OR									|
			|	int res = ncmp(str, other, n);			|
			|	//OR									|
			|	int res = str->m->ncmp(&str, other, n);	|
			*-------------------------------------------*
*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0 || !s1 || !s2)
		return ((s1 > s2) - (s1 < s2));
	while ((--n) && (*s1 != '\0') && (*s2 != '\0') && (*s1 == *s2))
	{
		++s1;
		++s2;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}

int32_t	_str_ncmp_char(t_str *this, const char *other, int32_t n)
{
	register int32_t	n1;

	if (str_check(this, NULL) || n < 0)
		return (_str_set_error(this, E_PARAM, "ncmp"), 0);
	n1 = this->i;
	while (n && this->buff[n1] && *other && this->buff[n1] == *other)
	{
		++n1;
		++other;
		--n;
	}
	return ((uint8_t)(this->buff[n1]) - (uint8_t)(*other));
}

int32_t	_str_ncmp_str(t_str *this, const t_str *other, int32_t n)
{
	register int32_t	n1;
	register int32_t	n2;

	if (str_check(this, NULL) || n < 0)
		return (_str_set_error(this, E_PARAM, "ncmp"), 0);
	n1 = this->i;
	n2 = other->i;
	while (n && this->buff[n1] && other->buff[n2] \
		&& this->buff[n1] == other->buff[n2])
	{
		++n1;
		++n2;
		--n;
	}
	return ((uint8_t)(this->buff[n1]) - (uint8_t)(other->buff[n2]));
}

/*
int	main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("Inserisci le 2 stringhe, poi il numero di confronti da fare");
		return (42);
	}
	if (argc == 42)
	{
		printf("Pisa merda");
		return (42);
	}
	int n = argv[3][0] - '0';
	printf("Funzione fake: %d", ft_strncmp(argv[1], argv[2], n));
	return (0);
}*/
