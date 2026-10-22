/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piscine_power.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 09:27:35 by alerusso          #+#    #+#             */
/*   Updated: 2025/02/20 12:14:00 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int	ft_iterative_power(int nb, int power);
/*
int main(int argc, char *argv[])
{
    int nb;
    int power;

    if (argc != 3)
    {
        printf("Arg[1] = n, Arg[2] = power\n");
        return (42);
    }
    nb = atoi(argv[1]);
    power = atoi(argv[2]);
    printf("La potenza di %d alla %d° è: ", nb, power);
    printf("%d\n", ft_iterative_power(nb, power));
    return (0);
}*/

int	ft_iterative_power(int nb, int power)
{
	int	nb_temp;

	if ((nb == 0) || (power == 0))
		return (1);
	if ((power <= 0) || (nb == 0))
		return (0);
	if ((nb == 1) && (power % 2 == 0) && (power < 0))
		return (1);
	if ((nb == 1) && (power % 2 == 1) && (power < 0))
		return (-1);
	if (power == 1)
		return (nb);
	nb_temp = nb;
	while (--power != 0)
		nb *= nb_temp;
	return (nb);
}
