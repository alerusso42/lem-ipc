/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:02:59 by alerusso          #+#    #+#             */
/*   Updated: 2025/12/12 18:34:33 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bfs.h"

static int	find_distance(t_bfs *bfs, int x, int y, int distance);
static int	process_one(t_bfs *bfs);
static int	bfs_loop(t_bfs *bfs, t_list2 *list);

//SECTION -	EXCHANGE DATA FROM YOUR STRUCT TO bfs_stuff
//			explaination at the end of the file

/*
int	get_best_path(t_data *data, int enemy_num)
{
	t_bfs	bfs_stuff;
	int		is_valid_path;

	bfs_stuff.en_x = data->enemy[enemy_num].pos[X];
	bfs_stuff.en_y = data->enemy[enemy_num].pos[Y];
	bfs_stuff.p_x = data->player.pos[X];
	bfs_stuff.p_y = data->player.pos[Y];
	bfs_stuff.map = data->map;
	bfs_stuff.map_x = data->game.map_size[X];
	bfs_stuff.map_y = data->game.map_size[Y];
	bfs_stuff.n = enemy_num;
	bfs_stuff.mark = (enemy_num + 1) * -1;
	clean_bfs(&bfs_stuff, enemy_num);
	bfs(&bfs_stuff);
	is_valid_path = draw_path(&bfs_stuff);
	if (is_valid_path == false)
	{
		//p_event_lost(map, enemy_num);
		return (false);
	}
	return (true);
}*/

/*
	1)	If you see a wall, or if distance is different than 0
		(if you already have been there), return.
	2)	Alloc for x, y;
	3)	Alloc a new node and register the distance of that node
		to the current + 1;
	4)	Add a node in the end of the list.
*/
static int	find_distance(t_bfs *bfs, int x, int y, int distance)
{
	t_list2	*new;
	t_list2	*list;
	int			*x_alloc;
	int			*y_alloc;

	if (ft_strchr(BFS_OBSTACLE, bfs->map[y][x].val) || \
	bfs->map[y][x].distance[bfs->n] != 0)
		return (2);
	x_alloc = ft_calloc(1, sizeof(int));
	if (!x_alloc)
		return (1);
	y_alloc = ft_calloc(1, sizeof(int));
	if (!y_alloc)
		return (1);
	*x_alloc = x;
	*y_alloc = y;
	new = lst2_new((void *)x_alloc, (void *)y_alloc);
	if (!new)
		return (FREE(x_alloc), FREE(y_alloc), 1);
	list = store_list(NULL, 1);
	if (bfs->map[y][x].distance[bfs->n] != -1)
		bfs->map[y][x].distance[bfs->n] = distance + 1;
	lst2_back(&list, new);
	return (0);
}

/*
	We process the position down, up, left, right.
	If the distance has reached 40, we stop.
*/
static int	process_one(t_bfs *bfs)
{
	if (bfs->distance >= BFS_MAX_DISTANCE)
		return (0);
	if ((bfs->x == bfs->p_x) && (bfs->y == bfs->p_y))
	{
		return (2);
	}
	if (find_distance(bfs, bfs->x + 1, bfs->y, bfs->distance) == 1)
		return (1);
	if (find_distance(bfs, bfs->x - 1, bfs->y, bfs->distance) == 1)
		return (1);
	if (find_distance(bfs, bfs->x, bfs->y + 1, bfs->distance) == 1)
		return (1);
	if (find_distance(bfs, bfs->x, bfs->y - 1, bfs->distance) == 1)
		return (1);
	return (0);
}

/*
	While the list exists:

	1)	We save the data of every node: (x, y, distance);
	2)	If the distance is -1 (start), it is considered as 0.
		If other node finds the start position, they'll still
		see the -1, recognizing it as the start position;
	3)	We process one node. Then we go to the next.
*/
static int	bfs_loop(t_bfs *bfs, t_list2 *list)
{
	int	*x;
	int	*y;

	while (list)
	{
		x = (int *)list->content1;
		y = (int *)list->content2;
		bfs->x = *x;
		bfs->y = *y;
		bfs->distance = bfs->map[bfs->y][bfs->x].distance[bfs->n];
		if (bfs->distance == -1)
			bfs->distance = 0;
		if (process_one(bfs) != 0)
			return (1);
		list = list->next;
	}
	return (0);
}

/*
	1)	We set the start position (enemy) to -1 in the distance
		map;
	2)	We give, as first node, the position of the enemy.
	3)	We need to malloc x and y, since we need to place them
		inside the node (they can't be stored as normal int:
		our list accepts only void * arguments);
	4)	We store the store the list in a static form;
	5)	We start the bfs loop;
	6)	We clear the list.
*/
void	bfs(t_bfs *bfs)
{
	t_list2		*list;
	t_list2		*tail;
	int				*x;
	int				*y;

	bfs->map[bfs->en_y][bfs->en_x].distance[bfs->n] = -1;
	x = ft_calloc(1, sizeof(int));
	if (!x)
		return ;
	y = ft_calloc(1, sizeof(int));
	if (!y)
		return ;
	*x = bfs->en_x;
	*y = bfs->en_y;
	bfs->x = *x;
	bfs->y = *y;
	list = lst2_new((void *)x, (void *)y);
	if (!list)
		return (FREE(x), FREE(y));
	tail = list;
	store_list(list, 0);
	bfs_loop(bfs, list);
	lst2_clear(&tail, del_free);
}

/*
	So. A LOT to say here.

	Why the bfs algorythm?
	
		1) 	The dfs alg. (floodfill) is very slow and resource
			hungry for this job (see dfs.c);
		2)	The bfs alg. requires low resources, and is very 
			fast;
		3)	We can apply it multiple times per second with
			more than 20 enemies, without any lag.
	How does the pathfinding algorythm work?
	-	Let's start by saying the enemies have a separate map.
	-	Their own percection, if you will.
	-	This perception is located in map->position: every 
		position in the map has a value ('P', 'E', ecc.) and 
		another variable, called distance.
	-	The distance variable is the unique enemy perception.
	
	This is what enemies see:

		-REAL MAP-				-BFS PROC-			-WHAT ENEMIES SEE-

		111111111				000000000				000000000			
		10$000011				01$123400				011000000
		100111001				021000560				010000000
		1000P0001				0345P7670				011110000
		111111111				000000000				000000000
	
	Let's take it step by step.
	We'll call the value map (the normal one) value map, the 
	enemy perception distance map.
		VALUE MAP:				DISTANCE MAP:

		111111111				000000000
		10$000011				000000000
		100111001				000000000
		1000P0001				000000000
		111111111				000000000
	1)	We place, in the distance map, -1, in the enemy position.
		I write only -, to graphic reason.
		VALUE MAP:				DISTANCE MAP:

		111111111				000000000
		10$000011				00-000000
		100111001				000000000
		1000P0001				000000000
		111111111				000000000
	
	2)	We place in every legal position near a 1.
		So, up, right, left.
		VALUE MAP:				DISTANCE MAP:

		111111111				000000000
		10$000011				01-100000
		100111001				001000000
		1000P0001				000000000
		111111111				000000000
	3)	We do the same, but starting with the 1, and writing 2.
		VALUE MAP:				DISTANCE MAP:

		111111111				000000000
		10$000011				01-120000
		100111001				021000000
		1000P0001				002000000
		111111111				000000000
	4)	The same, but starting with the 2, and writing 3.
		VALUE MAP:				DISTANCE MAP:

		111111111				000000000
		10$000011				01-123000
		100111001				021000000
		1000P0001				032300000
		111111111				000000000
	5)	We iterate through this process, until we find P, or there
		is nothing else to search.
		We place a -3 on the player (I only place -).
		VALUE MAP:				DISTANCE MAP:

		111111111				000000000			
		10$000011				01-123400
		100111001				021000560
		1000P0001				0345-7670
		111111111				000000000
	6)	We analyze this output in draw_path.
		See bfs_draw_path.c
	
	-	Ok, this is the theory.
		How do we do in practise?
	-	With nodes.
	-	Nodes are perfect for this job: when we find a new position,
		we simply add it with lst_addback: in this way, we
		analyze first the 1 distances, then the 2 distances, and
		so on.
	
		Well, that's it.
		-	For the data needed, we use a special struct, t_bfs.
		-	We declare it with the stack memory, since we don't
		 	need to use it anywhere else in the code.
		
		NOTES: 
		1)	I've limited the algorythm to a maximum 40 blocks
		chase: if you trigger an enemy and run 40 blocks away,
		bfs will fail.
		
		2)	Since I have multiple enemies, distance is not a char,
			like value, but a string of char.
		
*/
