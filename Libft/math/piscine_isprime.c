/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piscine_isprime.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 09:27:35 by alerusso          #+#    #+#             */
/*   Updated: 2025/02/18 10:50:23 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int	ft_is_prime(int nb);
/*
int main(int argc, char *argv[])
{
    int nb;

    if (argc != 2)
    {
        printf("Arg[1] = nb\n");
        return (42);
    }
    nb = atoi(argv[1]);
    if (ft_is_prime(nb) == 1)
        printf("%d è primo\n", nb);
    else
        printf("%d NON è primo\n", nb);
    return (0);
}*/
//Aumenta i fino alla metà di nb, fa resti iterativi.

int	ft_is_prime(int nb)
{
	int	i;

	if (nb <= 1)
		return (0);
	i = 2;
	while (((i) != ((nb / 2) + 1)) & (nb % i != 0))
		++i;
	if ((nb % i != 0) || (i == nb))
		return (1);
	else
		return (0);
}
// i == nb serve per il caso del numero 2.
