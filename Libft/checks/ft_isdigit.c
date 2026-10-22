/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:06:34 by alerusso          #+#    #+#             */
/*   Updated: 2025/12/12 18:36:56 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (true);
	else
		return (false);
}

/*
int	main()
{
	char	c;

	c = '^';
	if (ft_isdigit((int)c) == true)
		printf("\nTRUE\n");
	else
		printf("\nFALSE\n");
	return (0);
}*/
