/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:34:47 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/26 18:00:48 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "../../libft.h"

typedef struct s_list	t_list;

typedef struct s_list
{
	t_list	*next;
	t_list	*prev;
	void	*content;
}				t_list;

typedef struct s_list2
{
	void	*content1;
	void	*content2;
	void	*next;
}				t_list2;

#endif