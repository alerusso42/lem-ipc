/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 23:43:06 by alerusso          #+#    #+#             */
/*   Updated: 2026/02/09 14:58:49 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_internal.h"

int	__map_error(t_map *ptr, int code, void *data, const char *caller)
{
	MAP_LOG("Map Error:");
	if (code > MAP_SECTION_CRITICAL)
	{
		MAP_LOG("\033[31m Critical Error\033[0m");
		ptr->fail = true;
		map_clear(ptr);
	}
	MAP_LOG(" in function *%s*\n", caller);
	switch (code)
	{
	case MAP_OK:
		MAP_SWITCH_LOG("No errors found");
	case MAP_EXIST:
		MAP_SWITCH_LOG("Key %s already exist", data);
	case MAP_NOTFOUND :
		MAP_SWITCH_LOG("Key %s not found", data);
	case MAP_BUG:
		MAP_SWITCH_LOG("Bug: %s", data);
	case MAP_EINVAL:
	case MAP_INIT_EINVAL:
		MAP_SWITCH_LOG("Bad parameter");
	case MAP_NOMEM:
		MAP_SWITCH_LOG("Allocation failure");
	}
	MAP_LOG("\n");
	return (code);
}
