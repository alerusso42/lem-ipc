/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piscine_find_next_prime.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 09:27:35 by alerusso          #+#    #+#             */
/*   Updated: 2025/02/18 10:51:04 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int	ft_find_next_prime(int nb);
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
    printf("Il primo n primo successivo a %d è: ", nb);
    printf("%d\n", ft_find_next_prime(nb));
    return (0);
}*/
//Siamo al limite del barare qui, lol

int	ft_find_next_prime(int nb)
{
	if (nb <= 0)
		nb = 2;
	while (ft_is_prime(nb) != 1)
		++nb;
	return (nb);
}
// aumento fino a trovare un primo
