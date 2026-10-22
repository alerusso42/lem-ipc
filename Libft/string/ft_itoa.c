/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 12:46:20 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 17:21:21 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

static char	*alloc_string(char *allocated_string, int num, int *index);

char	*ft_itoa(int num)
{
	int		temp_num;
	int		index;
	char	*str;

	index = 0;
	temp_num = num;
	while ((temp_num > 9) || (temp_num < -9))
	{
		index++;
		temp_num /= 10;
	}
	str = NULL;
	str = alloc_string(str, num, &index);
	if (!str)
		return (NULL);
	str[index + 1] = '\0';
	while (num != 0)
	{
		if (num < 0)
			str[index--] = (((num % 10) * -1) + 48);
		else
			str[index--] = ((num % 10) + 48);
		num /= 10;
	}
	return (str);
}

static char	*alloc_string(char *allocated_string, int num, int *index)
{
	if (num < 0)
		*index += 1;
	allocated_string = (char *)CALLOC((*index) + 2, sizeof(char));
	if (!allocated_string)
		return (NULL);
	if (num < 0)
	{
		allocated_string[0] = '-';
	}
	if (num == 0)
	{
		allocated_string[(*index)] = '0';
	}
	return (allocated_string);
}

t_str	*str_itoa(t_str *this, int32_t value)
{
	char	*other;

	if (str_check(this, NULL))
		return (_str_set_error(this, E_PARAM, "itoa"), this);
	other = ft_itoa((int)value);
	if (!other)
		return (_str_set_error(this, E_ALLOC, "itoa"), this);
	return (str_push(this, other));
}

void	ft_itoa_stack(char *str, int64_t num)
{
	int64_t	temp_num;
	int		index;

	index = 0;
	if (num < 0)
		str[index++] = '-';
	if (num == 0)
		str[index] = '0';
	temp_num = num;
	while ((temp_num > 9) || (temp_num < -9))
	{
		index++;
		temp_num /= 10;
	}
	str[index + 1] = '\0';
	while (num != 0)
	{
		if (num < 0)
			str[index--] = (((num % 10) * -1) + 48);
		else
			str[index--] = ((num % 10) + 48);
		num /= 10;
	}
}

void	ft_uitoa_stack(char *str, uint64_t num)
{
	uint64_t	temp_num;
	int			index;

	index = 0;
	if (num == 0)
		str[index] = '0';
	temp_num = num;
	while (temp_num > 9)
	{
		index++;
		temp_num /= 10;
	}
	str[index + 1] = '\0';
	while (num != 0)
	{
		str[index--] = ((num % 10) + 48);
		num /= 10;
	}
}
