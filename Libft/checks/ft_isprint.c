/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:08:36 by alerusso          #+#    #+#             */
/*   Updated: 2025/12/12 18:36:30 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isprint(int c)
{
	if ((c <= 31) || (c >= 127))
		return (false);
	else
		return (true);
}

/*
int	main()
{
	char	c;

	c = '^';
	if (ft_isprint((int)c) == true)
		printf("\nTRUE\n");
	else
		printf("\nFALSE\n");
	return (0);
}*/
