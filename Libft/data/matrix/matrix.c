// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   matrix.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2026/03/22 22:18:19 by alerusso          #+#    #+#             */
// /*   Updated: 2026/03/22 23:03:24 by alerusso         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "matrix.h"

// //always return NULL
// void	*_matrix2_del(t_matr2 *matr2)
// {
// 	free_matrix(matr2->data);
// 	FREE(matr2);
// 	return (NULL);
// }

// //always return NULL
// void	*_matrix3_del(t_matr3 *matr3)
// {
// 	free_3d_matrix(matr3->data);
// 	FREE(matr3);
// 	return (NULL);
// }

// t_matr2	*matrix2_create(char const *s, char c)
// {
// 	t_matr2	*ptr;

// 	ptr = malloc(sizeof(t_matr2));
// 	if (!ptr)
// 		return (NULL);
// 	ptr->data = ft_split(s, c);
// 	if (!ptr->data)
// 		return (FREE(ptr->data), NULL);
// 	ptr->size = matrix2_len(ptr->data);
// 	ptr->del = _matrix2_del;
// 	return (ptr);
// }

// //matr_c: the separator of matrixes
// //str_c: the separator of strings
// t_matr3	*matrix3_create(const char *s, char matr_c, char str_c)
// {
// 	t_matr2	*ptr;

// 	ptr = malloc(sizeof(t_matr2));
// 	if (!ptr)
// 		return (NULL);
// 	ptr->data = ft_multi_split(s, matr_c, str_c);
// 	if (!ptr->data)
// 		return (FREE(ptr->data), NULL);
// 	ptr->size = matrix3_len(ptr->data);
// 	ptr->del = _matrix3_del;
// 	return (ptr);
// }

// // type 2: 2Dimensional matrix
// // type 3: 3Dimensional matrix
// // converts raw matrix in t_matr structure
// void	*matrix_convert(void *matr, int matr_type)
// {
// 	t_matr2	*ptr2;
// 	t_matr3	*ptr3;

// 	if (matr_type == 2)
// 	{
// 		ptr2 = malloc(sizeof(t_matr2));
// 		if (!ptr2)
// 			return (NULL);
// 		ptr2->data = matr;
// 		ptr2->size = matrix2_len(matr);
// 		return (ptr2);
// 	}
// 	else if (matr_type == 3)
// 	{
// 		ptr3 = malloc(sizeof(t_matr3));
// 		if (!ptr3)
// 			return (NULL);
// 		ptr3->data = matr;
// 		ptr3->size = matrix3_len(matr);
// 		return (ptr3);
// 	}
// 	return (NULL);
// }
