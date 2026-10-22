/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:34:47 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/26 16:41:32 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "../../libft.h"
# include "stdbool.h"

typedef struct	s_hlist
{
	void	*p;
	void	*half;
	void	*last;
	int32_t	len;
	bool	fail;
}				t_hlist;

typedef struct	s_list
{
	t_list	*next;
	t_list	*prev;
	void	*content;
}				t_list;

typedef struct s_list2
{
	t_list	*next;
	t_list	*prev;
	void	*content1;
	void	*content2;
}				t_list2;

#endif