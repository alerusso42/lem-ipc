/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piscine_sqrt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 09:27:35 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/27 12:26:20 by alerusso42       ###   ########.fr       */
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
	while ((i != 0) && (i * i != nb))
		--i;
	return (i);
}
