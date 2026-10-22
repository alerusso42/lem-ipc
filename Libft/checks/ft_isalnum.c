/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:06:34 by alerusso          #+#    #+#             */
/*   Updated: 2025/12/12 18:36:53 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

int	ft_isalnum(int c)
{
	if ((ft_isalpha(c) == true) || (ft_isdigit(c) == true))
		return (true);
	else
		return (false);
}

/*
int	main()
{
	char	c;

	c = '^';
	if (ft_isalnum((int)c) == true)
		printf("\nTRUE\n");
	else
		printf("\nFALSE\n");
	return (0);
}*/
