/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:07:48 by alerusso          #+#    #+#             */
/*   Updated: 2026/01/05 18:23:57 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

int	int_size(int64_t n)
{
	int	len;

	if (!n)
		return (1);
	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	uint_size(uint64_t n)
{
	int	len;

	if (!n)
		return (1);
	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}
