/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:12:08 by alerusso          #+#    #+#             */
/*   Updated: 2026/02/09 15:07:44 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define RED 	"FF0000"
#define GREEN 	"00FF00"
#define BLUE 	"0000FF"

void	del(t_map_val *pair);

int	alloc(t_map_val *pair, char *key, void *val)
{
	pair->key = ft_strdup(key);
	pair->val = ft_strdup(val);
	if (!pair->key || !pair->val)
		return (del(pair), 1);
	return (0);
}

void	del(t_map_val *pair)
{
	FREE(pair->key);
	FREE(pair->val);
	FREE(pair);
}

int	main()
{
	t_map	map;

	if (map_init(&map, 5) != 0)
		return (1);
	map.alloc = alloc;
	map.del = del;
	map_add(&map, "RED", RED);
	map_add(&map, "GREEN", GREEN);
	if (map_find(&map, "REDD") == true)
		map_del(&map, "REDD");
	map_add(&map, "BLUE", BLUE);
	ft_printf("map values: RED{%s}GREEN{%s}BLUE{%s}\n", \
	map_get(&map, "RED"), map_get(&map, "GREEN"), map_get(&map, "BLUE"));
	map_free(&map);
}
