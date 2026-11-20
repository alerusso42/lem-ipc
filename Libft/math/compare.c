/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 11:56:40 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/20 12:01:38 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

int64_t	ft_max(int64_t x, int64_t y)
{
	return (x > y ? x : y);
}

int64_t	ft_max3(int64_t x, int64_t y, int64_t z)
{
	int	n;

	n = x > y ? x : y;
	n = n > z ? n : z;
	return (n);
}

int64_t	ft_min(int64_t x, int64_t y)
{
	return (x < y ? x : y);
}

int64_t	ft_min3(int64_t x, int64_t y, int64_t z)
{
	int	n;

	n = x < y ? x : y;
	n = n < z ? n : z;
	return (n);
}
