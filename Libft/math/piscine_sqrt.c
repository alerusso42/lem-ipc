/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piscine_sqrt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 09:27:35 by alerusso          #+#    #+#             */
/*   Updated: 2025/02/18 10:49:46 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int	ft_sqrt(int nb);
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
    printf("La radice quadrata di %d è: ", nb);
    printf("%d\n", ft_sqrt(nb));
    return (0);
}*/
// Si calcola tutti gli n^2 <= nb / 2 (M. iterativo).

int	ft_sqrt(int nb)
{
	int	i;

	if (nb <= 0)
		return (0);
	if (nb == 1)
		return (1);
	i = nb / 2;
	while ((i != 0) & (i * i != nb))
		--i;
	if (i * i != nb)
		i = 0;
	return (i);
}
// Se non li trova, esce dal while e (48) setta i = 0
