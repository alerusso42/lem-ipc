/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 08:35:31 by codespace         #+#    #+#             */
/*   Updated: 2026/01/16 20:31:55 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prog.h"

/*
//REVIEW -	daft_swap
//
	In daft.h, there is an enum, called e_daft_db.
	You can pass those enum to daft_swap, to change database.

	Note: enum names can be changed in SETTINGS.md
*/
void	daft_swap(int enum_id)
{
	t_daft_data	*data;

	data = _daft_get_memory(NULL, false);
	if (!data)
		return ((void)_daft_log(DAFT_LOG_NOMEM));
	if (enum_id >= data->files_num || enum_id < 0)
		return ((void)_daft_log(DAFT_LOG_ENUM_ID));
	data->current_file = enum_id;
}
