// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   class_matr_convert.c                               :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2026/03/22 23:04:25 by alerusso          #+#    #+#             */
// /*   Updated: 2026/03/22 23:54:54 by alerusso         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "string.h"
#include "string_private.h"

// void	*str_matrix2_free(t_str **matrix);
// void	*str_matrix3_free(t_str ***matrix);

// t_str	**str_convert_matrix2(char **matr, int size)
// {
// 	t_str	**str_arr;
// 	int		i;

// 	if (!matr)
// 		return (NULL);
// 	str_arr = ft_calloc(size + 1, sizeof(t_str *));
// 	if (!str_arr)
// 		return (NULL);
// 	i = 0;
// 	while (matr[i])
// 	{
// 		str_arr[i] = ft_calloc(1, sizeof(t_str));
// 		if (!str_arr[i])
// 			return (str_matrix2_free(str_arr));
// 		str_new(&str_arr[i], matr[i]);
// 		i += 1;
// 	}
// 	return (str_arr);
// }

// t_str	***str_convert_matrix3(char ***matr, int size)
// {
// 	int		i;
// 	t_str	***str_arr;

// 	if (!matr)
// 		return (NULL);
// 	str_arr = ft_calloc(size + 1, sizeof(t_str **));
// 	if (!str_arr)
// 		return (NULL);
// 	i = 0;
// 	while (matr[i])
// 	{
// 		str_arr[i] = _str_convert_matrix2(matr[i], str_arr);
// 		if (!str_arr[i])
// 			return (str_matrix3_free(str_arr));
// 		i++;
// 	}
// 	return (str_arr);
// }

// /*
// 	Always return NULL
// */
// void	*str_matrix2_free(t_str **matrix)
// {
// 	int	index;

// 	index = 0;
// 	if (!matrix)
// 		return (NULL);
// 	while (matrix[index])
// 	{
// 		if (matrix[index])
// 			str_delete(matrix[index]);
// 		matrix[index] = NULL;
// 		++index;
// 	}
// 	if (matrix)
// 		FREE(matrix);
// 	return (NULL);
// }

// /*
// 	Always return NULL
// */
// void	*str_matrix3_free(t_str ***matrix)
// {
// 	int	index_one;
// 	int	index_two;

// 	index_one = 0;
// 	if (!matrix)
// 		return (NULL);
// 	while (matrix[index_one])
// 	{
// 		index_two = 0;
// 		while (matrix[index_one][index_two])
// 		{
// 			str_delete(matrix[index_one][index_two]);
// 			matrix[index_one][index_two] = NULL;
// 			++index_two;
// 		}
// 		FREE(matrix[index_one]);
// 		matrix[index_one] = NULL;
// 		++index_one;
// 	}
// 	FREE(matrix);
// 	return (NULL);
// }
