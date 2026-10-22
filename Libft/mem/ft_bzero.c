/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:37:29 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/27 16:43:59 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*string_pointer;
	size_t	stop_process;

	string_pointer = (char *)s;
	stop_process = 0;
	while (stop_process != n)
	{
		string_pointer[stop_process] = 0;
		++stop_process;
	}
}
