/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 23:11:57 by alerusso          #+#    #+#             */
/*   Updated: 2026/01/02 12:48:57 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prog.h"

/*
//REVIEW -	daft_load
//	Update all files opened with successful calls of daft_append() and 
	daft_edit().
//	Memories pointers connected to daft_append(), daft_edit(), daft_get()
	are freed.
	Using them later bring undefined behaviour.
*/
int	daft_load(void)
{
	int			curr_file;
	int			exit_code;
	char		*path;
	char		*sett_filename;
	t_daft_data	*data;

	data = _daft_get_memory(NULL, false);
	if (!data)
		return (_daft_log(DAFT_LOG_NOMEM));
	curr_file = data->current_file;
	path = ft_strdup(data->conf.path);
	sett_filename = ft_strdup(data->conf.sett_path);
	daft_quit();
	exit_code = daft_init(path, sett_filename);
	data = _daft_get_memory(NULL, false);
	if (data)
		data->current_file = curr_file;
	return (exit_code);
}
