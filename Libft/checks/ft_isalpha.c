/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:15:56 by alerusso          #+#    #+#             */
/*   Updated: 2025/12/12 18:36:46 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isalpha(int c);

int	ft_isalpha(int c)
{
	if ((c >= 'a') && (c <= 'z'))
		return (true);
	if ((c >= 'A') && (c <= 'Z'))
		return (true);
	else
		return (false);
}

/*
int	main()
{
	char	c;

	c = '^';
	if (ft_isalpha((int)c) == true)
		printf("\nTRUE\n");
	else
		printf("\nFALSE\n");
	return (0);
}*/
