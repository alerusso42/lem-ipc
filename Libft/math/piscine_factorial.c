/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piscine_factorial.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 09:27:35 by alerusso          #+#    #+#             */
/*   Updated: 2025/02/20 12:41:51 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int	ft_iterative_factorial(int nb);
/*
int main(int argc, char *argv[])
{
    int nb;

    if (argc != 2)
    {
        printf("Arg[1] = n");
        return (42);
    }
    nb = atoi(argv[1]);
    printf("Il fattoriale di %d è: %d", nb, ft_iterative_factorial(nb));
    return (0);
}
*/

int	ft_iterative_factorial(int nb)
{
	int	stop;
	int	num_list;

	if (nb < 0)
		return (0);
	if ((nb == 0) || (nb == 1))
		return (1);
	stop = nb - 1;
	num_list = 2;
	nb = 1;
	while (stop != 0)
	{
		nb = num_list * nb;
		++num_list;
		--stop;
	}
	return (nb);
}
