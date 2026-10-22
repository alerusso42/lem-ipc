/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 10:04:32 by alerusso          #+#    #+#             */
/*   Updated: 2025/09/27 22:15:36 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prog.h"

/*
//REVIEW -	daft_edit
//
	Modify data in a file in the user database.
	File chosen must be chosen using daft_switch().
	On success, returns the current data in the file; you can modify
	it as you want.
	When daft_load() or daft_quit() are called, every buffer returned with
	daft_edit() overrides the files old content.
	Parameters:	
				key:		the key of the data you need to modify;
				size:		the size in memory of the strings allocated;
				mtr_number:	the number of matrix allocated.

	Therefore, if you need to modify in the data:
	RUNNER_GIOVANNI%	------------->	RUNNER_GIOVANNI%
	speed=12 km/h		------------->	speed=250 km/h
	endurance=25 km		------------->	endurance=3000 km
	time training=30 minutes	----->	time training=120 minutes

	you should call:
	----------------------------------------------------
	char	**mtr;

	mtr = daft_edit("RUNNER_GIOVANNI", 11, 3);
	if (!mtr)
		return (1);
	----------------------------------------------------
	11:	the size of the longest string, "120 minutes";
	3:	the number of matrix needed (speed, endurance, time training).

	If key does not exist, daft_edit() fails.
	If daft_edit is called on the same key multiple times, only most
	recent call is considered; others are just ignored.
*/
void	*daft_edit(const char *search, int size, int mtr_number)
{
	t_daft_data	*data;
	void		*mem;

	if (!search)
		return (NULL);
	if (size < 0)
		size = 0;
	if (mtr_number <= 0)
		mtr_number = 1;
	data = _daft_get_memory(NULL, false);
	if (!data)
		return ((void)_daft_log(DAFT_LOG_NOMEM), NULL);
	data->minimal_alloc_size = size;
	data->minimal_matrix_num = mtr_number;
	mem = daft_get(search);
	data->minimal_alloc_size = 0;
	data->minimal_matrix_num = 1;
	if (mem)
		data->data_list[data->current_file]->edit = true;
	return (mem);
}
