/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft_utils_strings.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:21:04 by alerusso          #+#    #+#             */
/*   Updated: 2025/09/23 19:35:01 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prog.h"

/*REVIEW - cat_string

//Cat a string in another string, starting from start (included).
*/
static void	to_free(char *s1, char *s2, int which);

// usage: new = _cat_string(src, catstr, 4, 2);
//	src = "Hello";	catstr = " World"; start = 5; which_free = 2;
//	new = "Hello World"
//
//	which_free: 0 FREE NOTHING, 1 FREE src, 2 FREE catstr, 3 FREE BOTH	
char	*_cat_string(char *src, char *catstr, size_t start, int which_free)
{
	size_t	i;
	char	*new;
	size_t	catstr_len;

	if (!src || !catstr)
		return (to_free(src, catstr, which_free), NULL);
	i = 0;
	while (src[i] && i < start)
		++i;
	if (i > start && !src[i])
		return (to_free(src, catstr, which_free), NULL);
	catstr_len = ft_strlen(catstr);
	new = (char *)ft_calloc(ft_strlen(src) + catstr_len + 2, sizeof(char));
	if (new)
	{
		ft_strlcpy(new, src, start + 2);
		ft_strlcpy(new + start, catstr, catstr_len + 2);
		if (src[i])
			sub_strcpy(new + start + catstr_len, src + start, "", EXCLUDE);
	}
	return (to_free(src, catstr, which_free), new);
}

static void	to_free(char *s1, char *s2, int which)
{
	if (which == 1 || which >= 3)
		free(s1);
	if (which == 2 || which >= 3)
		free(s2);
}
