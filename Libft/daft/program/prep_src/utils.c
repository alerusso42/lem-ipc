/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:33:07 by codespace         #+#    #+#             */
/*   Updated: 2025/09/21 11:12:10 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prep.h"

void	_daft_make_float(t_daft_prep *data, char *str, double *result)
{
	long long int	atoi_check;
	int				dot_i;
	int				decimal_part;

	atoi_check = 0;
	dot_i = sub_strlen(str, ".", EXCLUDE);
	if (str[dot_i])
		atoi_check = ft_atoi(str + dot_i + 1);
	if (atoi_check > INT_MAX || atoi_check < INT_MIN)
		_daft_prep_error(data, ER_ATOI);
	decimal_part = atoi_check;
	str[dot_i] = 0;
	atoi_check = ft_atoi(str);
	if (atoi_check > INT_MAX || atoi_check < INT_MIN)
		_daft_prep_error(data, ER_ATOI);
	*result = atoi_check;
	dot_i = _daft_num_size(decimal_part);
	while (decimal_part)
	{
		*result += (decimal_part % 10) / (double)dot_i;
		decimal_part /= 10;
		dot_i /= 10;
	}
}

int	_daft_num_size(int n)
{
	int	i;

	i = 1;
	while (n)
	{
		n /= 10;
		i *= 10;
	}
	return (i);
}

int		_daft_count_char(char *str, char c)
{
	int	counter;

	counter = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == c)
			counter += 1;
		++str;
	}
	return (counter);
}

int	_daft_ft_abs(int n)
{
	if (n == INT_MIN)
		return (INT_MAX);
	if (n < 0)
		n *= -1;
	return (n);
}

void	_daft_find_lowest_key(t_daft_prep *data, int *lowest_key, int *struct_i)
{
	int	i;
	int	curr_lowest;
	int	curr_i;

	i = 1;
	curr_lowest = INT_MAX;
	curr_i = 0;
	while (i != data->hash_size)
	{
		if (data->hash_table[i].key != -1 && \
			data->hash_table[i].key < curr_lowest && \
			data->hash_table[i].key >= *lowest_key && \
			i != *struct_i && \
			_daft_coll_check(data, data->hash_table[i].key) == 0)
		{
			curr_lowest = data->hash_table[i].key;
			curr_i = i;
		}
		++i;
	}
	*lowest_key = curr_lowest;
	*struct_i = curr_i;
	if (curr_lowest == INT_MAX)
		*lowest_key = -1;
}
