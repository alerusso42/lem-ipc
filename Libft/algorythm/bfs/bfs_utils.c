/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 07:51:51 by alerusso          #+#    #+#             */
/*   Updated: 2025/12/12 18:34:46 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bfs.h"

//
/*
	Delete the nodes with lstclear.
*/
void	del_free(void *ptr)
{
	FREE(ptr);
	ptr = NULL;
}

//////////////////////////////////////////////

/*
	A store to the list used for bfs.
*/
t_list2	*store_list(t_list2 *list, int mode)
{
	static t_list2	*store_list;

	if (mode == 0)
	{
		store_list = list;
		return (NULL);
	}
	return (store_list);
}

/*
	Clear the path of the enemy.
	Very important to call before using bfs.
*/
void	clean_bfs(t_bfs *bfs, int enemy_num)
{
	int	x;
	int	y;

	y = 0;
	while (y != bfs->map_y)
	{
		x = 0;
		while (x != bfs->map_x)
		{
			if (bfs->map[y][x].distance)
				bfs->map[y][x].distance[enemy_num] = 0;
			++x;
		}
		++y;
	}
}
