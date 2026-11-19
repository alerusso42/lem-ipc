/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DEMO.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:02:59 by alerusso          #+#    #+#             */
/*   Updated: 2026/02/09 12:26:45 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

typedef struct s_position
{
	char	value;
	char	distance;
}				t_position;

typedef struct s_bfs
{
	int			n;
	int			en_x;
	int			en_y;
	int			p_x;
	int			p_y;
	int			x;
	int			y;
	int			map_x;
	int			map_y;
	t_position	**position;
	int			distance;
}				t_bfs;

//PER COMPILARE: cc bfs_copy.c libft.a

#define MAP_X 20
#define MAP_Y 20

#define PRINT 1
#define WALL 6

#define NO 0
#define YES 1

int	en_x;
int	en_y;
int	p_x;
int	p_y;


void	set_entity(t_position **position, char e)
{
	int	x;
	int	y;

	while ("loop")
	{
		x = rand();
		y = rand();
		if (position[x % MAP_X][y % MAP_Y].value != '1')
		{
			position[x % MAP_X][y % MAP_Y].value = e;
			break ;
		}
	}
}

void	initialize_center(t_position **position)
{
	int	x;
	int	y;
	int	random;

	x = 0;
	y = 1;
	while ((++x) || (1))
	{
		if (x == MAP_X - 1)
		{
			if (y == MAP_Y - 1)
				break ;
			y++;
			x = 1;
		}
		random = rand();
		if (random % WALL == 0)
			position[x][y].value = '1';
		else
			position[x][y].value = '0';
		position[x][y].distance = 0;
	}
}

void	set_to_zero(t_position **position)
{
	int			x;
	int			y;

	x = -1;
	y = -1;
	while (++y != MAP_Y + 1)
	{
		x = -1;
		while (++x != MAP_X + 1)
		{
			position[x][y].value = '1';
			position[x][y].distance = 0;
		}
	}
}

void	initialize_map(t_position **position)
{
	int			x;
	int			y;

	x = -1;
	y = 0;
	set_to_zero(position);
	while ((++x) || (1))
	{
		if (x == MAP_X - 1)
		{
			if (y == MAP_Y - 1)
				break ;
			y = MAP_Y - 1;
			x = 0;
		}
		position[x][y].value = '1';
		position[x][y].distance = 0;
	}
	y = -1;
	x = 0;
	while ((++y) || (1))
	{
		if (y == MAP_Y)
		{
			if (x == MAP_X - 1)
				break ;
			x = MAP_X - 1;
			y = 0;
		}
		position[x][y].value = '1';
		position[x][y].distance = 0;
	}
	position[MAP_X - 1][MAP_Y - 1].value = '1';
	position[MAP_X - 1][MAP_Y - 1].distance = 0;
	initialize_center(position);
}

void	get_pos(t_position **position)
{
	int	x;
	int	y;

	x = 0;
	y = 1;
	while ((++x) || (1))
	{
		if (x == MAP_X - 1)
		{
			if (y == MAP_Y - 1)
				break ;
			y++;
			x = 1;
		}
		if (position[x][y].value == 'P')
		{
			p_x = x;
			p_y = y;
		}
		if (position[x][y].value == '$')
		{
			en_x = x;
			en_y = y;
		}
	}
}

void	print(t_position **position)
{
	int	x;
	int	y;
	char	c;

	x = -1;
	y = 0;
	printf("\nMap values: \n y = %d:\n", y);
	while ((++x) || (1))
	{
		if (x == MAP_X)
		{
			printf("\ny= %d:\n", y);
			if (y == MAP_Y)
				break ;
			y++;
			x = 0;
		}
		c = position[x][y].value;
		if (c == '0')
			printf("\033[1;37m%c\033[0m | ", c);
		else if (c == '1')
			printf("\033[1;35m%c\033[0m | ", c);
		else if (c == '$')
			printf("\033[1;31m%c\033[0m | ", c);
		else
			printf("\033[1;32m%c\033[0m | ", c);
		//\033[1;31mThis is red text\033[0m
	}
	x = 0;
	y = 0;
	printf("\n\n\nMap distances: \n\n");
	while ((++x) || (1))
	{
		if (x == MAP_X)
		{
			printf("\n\n");
			if (y == MAP_Y)
				break ;
			y++;
			x = 0;
		}
		if (position[x][y].distance == -1)
			printf("\033[1;33m%2d\033[0m | ", position[x][y].distance);
		else if (position[x][y].distance == -2)
			printf("\033[1;31m%2d\033[0m | ", position[x][y].distance);
		else if (position[x][y].distance == -3)
			printf("\033[1;32m%2d\033[0m | ", position[x][y].distance);
		else
			printf("%2d | ", position[x][y].distance);
	}
}

void	del(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

//////////////////////////////////////////////

t_typelist	*store_list(t_typelist *list, int mode)
{
	static t_typelist	*store_list;
	
	if (mode == 0)
	{
		store_list = list;
		return (NULL);
	}
	return (store_list);
}

int	find_distance(t_position **position, int x, int y, int distance)
{
	t_typelist	*new;
	t_typelist	*list;
	int			*x_alloc;
	int			*y_alloc;
	
	if ((position[x][y].value == '1') || (position[x][y].distance != 0))
		return (2);
	x_alloc = ft_calloc(1, sizeof(int));
	if (!x_alloc)
		return (1);
	y_alloc = ft_calloc(1, sizeof(int));
	if (!y_alloc)
		return (1);
	*x_alloc = x;
	*y_alloc = y;
	new = ft_lstnew((void *)x_alloc, (void *)y_alloc);
	if (!new)
		return (free(x_alloc), free(y_alloc), 1);
	list = store_list(NULL, 1);
	if (position[x][y].distance != -1)
		position[x][y].distance = distance + 1;
	ft_lstadd_back(&list, new);
	return (0);
}

int	process_one(t_bfs *bfs)
{
	if ((bfs->x == bfs->p_x) && (bfs->y == bfs->p_y))
	{
		return (2);
	}
	if (find_distance(bfs->position, bfs->x + 1, bfs->y, bfs->distance) == 1)
		return (1);
	if (find_distance(bfs->position, bfs->x - 1, bfs->y, bfs->distance) == 1)
		return (1);
	if (find_distance(bfs->position, bfs->x, bfs->y + 1, bfs->distance) == 1)
		return (1);
	if (find_distance(bfs->position, bfs->x, bfs->y - 1, bfs->distance) == 1)
		return (1);
	return (0);
}

int	bfs_loop(t_bfs *bfs, t_typelist *list)
{
	int	*x;
	int	*y;

	while (list)
	{
		x = (int *)list->content;
		y = (int *)list->type;
		bfs->x = *x;
		bfs->y = *y;
		bfs->distance = bfs->position[bfs->x][bfs->y].distance;
		if (bfs->distance == -1)
			bfs->distance = 0;
		if (process_one(bfs) != 0)
			return (1);
		if (PRINT == 3)
			print(bfs->position);
		list = list->next;
	}
	return (0);
}

void	bfs(t_bfs *bfs);

void	bfs(t_bfs *bfs)
{
	t_typelist		*list;
	t_typelist		*tail;
	int				*x;
	int				*y;

	bfs->position[bfs->en_x][bfs->en_y].distance = -1;
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
	list = ft_lstnew((void *)x, (void *)y);
	if (!list)
		return (free(x), free(y));
	tail = list;
	store_list(list, 0);
	bfs_loop(bfs, list);
	ft_lstclear(&tail, del);
}

int	find_shortest_route(t_position **position, int x, int y)
{
	int	record;

	record = 2000000;
	if (position[x + 1][y].distance > 0)
		record = position[x + 1][y].distance;
	if ((position[x - 1][y].distance > 0) && \
	(position[x - 1][y].distance < record))
		record = position[x - 1][y].distance;
	if ((position[x][y + 1].distance > 0) && \
	(position[x][y + 1].distance < record))
		record = position[x][y + 1].distance;
	if ((position[x][y - 1].distance > 0) && \
	(position[x][y - 1].distance < record))
		record = position[x][y - 1].distance;
	if (record == position[x + 1][y].distance)
		return (1);
	if (record == position[x - 1][y].distance)
		return (2);
	if (record == position[x][y + 1].distance)
		return (3);
	if (record == position[x][y - 1].distance)
		return (4);
	return (-1);
}

int		found_end(int x, int y, int stop_x, int stop_y)
{
	if ((x + 1 == stop_x) && (y == stop_y))
		return (1);
	if ((x - 1 == stop_x) && (y == stop_y))
		return (1);
	if ((x == stop_x) && (y + 1 == stop_y))
		return (1);
	if ((x == stop_x) && (y - 1 == stop_y))
		return (1);
	return (0);
}

void	update_one(t_position **position, int *x, int *y, int rec)
{
		if (rec == 1)
		{
			position[*x + 1][*y].distance = -1;
			(*x)++;
		}
		if (rec == 2)
		{
			position[*x - 1][*y].distance = -1;
			(*x)--;
		}
		if (rec == 3)
		{
			position[*x][*y + 1].distance = -1;
			(*y)++;
		}
		if (rec == 4)
		{
			position[*x][*y - 1].distance = -1;
			(*y)--;
		}
}

void	normalize_path(t_position **position)
{
	int			x;
	int			y;

	x = -1;
	y = -1;
	while (++y != MAP_Y + 1)
	{
		x = -1;
		while (++x != MAP_X + 1)
		{
			if (position[x][y].distance > 0)
				position[x][y].distance = 0;
		}
	}
}

int	draw_path(t_bfs *bfs)
{
	int	stop_x;
	int	stop_y;
	int	record;

	bfs->x = bfs->p_x;
	bfs->y = bfs->p_y;
	stop_x = bfs->en_x;
	stop_y = bfs->en_y;
	bfs->position[bfs->x][bfs->y].distance = -3;
	if (find_shortest_route(bfs->position, bfs->x, bfs->y) == -1)
	{
		return (normalize_path(bfs->position), NO);
	}
	while ((bfs->x != stop_x) || (bfs->y != stop_y))
	{
		if (found_end(bfs->x, bfs->y, stop_x, stop_y) == YES)
		{
			bfs->position[bfs->en_x][bfs->en_y].distance = -2;
			break ;
		}
		record = find_shortest_route(bfs->position, bfs->x, bfs->y);
		update_one(bfs->position, &bfs->x, &bfs->y, record);
		if (PRINT >= 4)
			print(bfs->position);
	}
	return (normalize_path(bfs->position), YES);
}

void	prepare_bfs_1(t_bfs *bfs, int en_x, int en_y)
{
	bfs->en_x = en_x;
	bfs->en_y = en_y;
	(void)en_x;
	(void)en_y;
}

void	prepare_bfs_2(t_bfs *bfs, int p_x, int p_y, t_position **position)
{
	bfs->p_x = p_x;
	bfs->p_y = p_y;
	bfs->position = position;
}

static int	free_tesMap(t_position ***position)
{
	t_position	**save;
	
	save = *position;
	while (**position)
	{
		free(**position);
		**position = NULL;
		(*position)++;
	}
	*position = save;
	free(*position);
	*position = NULL;
	return (0);
}

static int	alloc_tesMap(t_position ***position)
{
	int	y;
	int	total_size;
	int	index;

	if (!position)
		return (2);
	total_size = (MAP_X * MAP_Y) + (MAP_X * 2);
	*position = (t_position **)ft_calloc(total_size, sizeof(t_position *));
	if (!(*position))
		return (1);
	y = MAP_Y + 1;
	index = 0;
	while (y--)
	{
		(*position)[index] = (t_position *)ft_calloc\
		(MAP_Y + 1, sizeof(t_position));
		if (!(*position)[index])
			return (free_tesMap(position));
		++index;
	}
	return (0);
}

int	main()
{
	t_position			**position;
	static t_bfs		bfs_stuff;
	int					is_valid_path;

	if (WALL <= 1)
		return (printf("\nWALL deve essere minimo 2\n"));
	if (alloc_tesMap(&position) == 1)
		return (1);
	initialize_map(position);
	set_entity(position, 'P');
	set_entity(position, '$');
	if (PRINT >= 2)
		print(position);
	get_pos(position);
	prepare_bfs_1(&bfs_stuff, en_x, en_y);
	prepare_bfs_2(&bfs_stuff, p_x, p_y, position);
	bfs(&bfs_stuff);
	if (PRINT >= 2)
		print(position);
	is_valid_path = draw_path(&bfs_stuff);
	if (PRINT >= 1)
		print(position);
	if (is_valid_path == YES)
		printf("\n\nTrovato un path valido!\n");
	if (is_valid_path == NO)
		printf("\n\nNessun path valido!\n");
	free_tesMap(&position);
	exit(0);
}*/