/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:34:47 by alerusso          #+#    #+#             */
/*   Updated: 2026/04/23 12:18:40 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "../../libft.h"

char	***ft_multi_split(char *s, char matr_c, char str_c);
int		matrix2_len(char **matr);
int		matrix3_len(char ***matr);
void	*free_matrix(void **matrix);
void	*free_three_d_matrix(void ***matrix);

typedef struct s_matr2
{
	size_t	size;
	char	**data;
	void	(*del)(struct s_matr2 *);
}				t_matr2;

typedef struct s_matr3
{
	size_t	size;
	char	***data;
	void	(*del)(struct s_matr3 *);
}				t_matr3;

#endif