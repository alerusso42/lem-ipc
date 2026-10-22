/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 21:29:14 by alerusso          #+#    #+#             */
/*   Updated: 2026/04/23 12:18:31 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

// returns strings in matrix
int	matrix2_len(char **matr)
{
	int	i;

	i = 0;
	if (!matr)
		return (0);
	while (*matr)
	{
		matr++;
		i++;
	}
	return (i);
}

// returns strings in all matrixes
int	matrix3_len(char ***matr)
{
	int	i;

	i = 0;
	if (!matr)
		return (0);
	while (matr)
	{
		i += matrix2_len(*matr);
		matr++;
	}
	return (i);
}

/*
	Always return NULL
*/
void	*free_matrix(void **matrix)
{
	int	index;

	index = 0;
	if (!matrix)
		return (NULL);
	while (matrix[index])
	{
		if (matrix[index])
			FREE(matrix[index]);
		matrix[index] = NULL;
		++index;
	}
	if (matrix)
		FREE(matrix);
	return (NULL);
}

/*
	Always return NULL
*/
void	*free_three_d_matrix(void ***matrix)
{
	int	index_one;
	int	index_two;

	index_one = 0;
	if (!matrix)
		return (NULL);
	while (matrix[index_one])
	{
		index_two = 0;
		while (matrix[index_one][index_two])
		{
			FREE(matrix[index_one][index_two]);
			matrix[index_one][index_two] = NULL;
			++index_two;
		}
		FREE(matrix[index_one]);
		matrix[index_one] = NULL;
		++index_one;
	}
	FREE(matrix);
	return (NULL);
}
