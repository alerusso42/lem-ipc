/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 12:38:45 by alerusso          #+#    #+#             */
/*   Updated: 2026/01/06 12:42:09 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_data.h"

void	_error(t_ft_printf *data, char *err, int err_len)
{
	print_str_len(data, err, err_len);
	data->s += sub_strlen(data->s, "", EXCLUDE);
}
