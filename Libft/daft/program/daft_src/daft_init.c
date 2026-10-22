/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 22:36:58 by alerusso          #+#    #+#             */
/*   Updated: 2026/01/02 12:45:03 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prog.h"

static int	get_settings_file(t_daft_data *data);
static int	get_database_file(t_daft_data *data);

/*
//REVIEW -	daft_init
//
	You must give as a parameter:
	1)	the path of your data directory;
	2)	the name of the settings file.
	Initialize daft memory.
	Returns 0 on success.
*/
int 	daft_init(const char *path, const char *settings_filename)
{
	t_daft_data	*data;
	char		*temp;

	if (_daft_get_memory(NULL, false) || !path || !settings_filename)
		return (_daft_log(DAFT_LOG_USAGE));
	data = ft_calloc(1, sizeof(t_daft_data));
	if (!data)
		return (DAFT_LOG_MALLOC);
	data->conf.debug_log = true;
	data->conf.path = ft_strdup(path);
	temp = ft_strjoin(path, "/");
	data->conf.sett_path = ft_strjoin(temp, settings_filename);
	FREE(temp);
	data->conf.tmp_path = ft_strjoin(path, "/tmp.dft");
	//data->conf.log_path = ft_strjoin(path, "/log.dft"); //to log in a file
	data->mem_size = -1;
	data->minimal_matrix_num = 1;
	_daft_get_memory(data, true);
	if (get_settings_file(data) != 0)
		return (daft_quit(), 1);
	if (get_database_file(data) != 0)
		return (daft_quit(), 1);
	return (0);
}

//	All setting file is read, searching for the two section of
//	settings.
static int	get_settings_file(t_daft_data *data)
{
	char	*line;
	t_fd	settings_file;

	settings_file = openfd(data->conf.sett_path, "r");
	if (!settings_file.n)
		return (_daft_log(DAFT_LOG_SETT));
	line = gnl();
	while (line)
	{
		if (!ft_strncmp(line, "#SECTION - General settings", 27))
		{
			if (_daft_save_config(data) == DAFT_LOG_MALLOC)
				closefd(settings_file);
		}
		else if (!ft_strncmp(line, "#SECTION - Files flags", 22))
		{
			if (_daft_save_fnames(data) == DAFT_LOG_MALLOC)
				closefd(settings_file);
		}
		FREE(line);
		line = gnl();
	}
	return (closefd(settings_file), 0);
}

//	For every file, a dedicated struct is allocated.
//	The struct stores its inner flags, its filename, 
static int	get_database_file(t_daft_data *data)
{
	int	i;

	data->data_list = ft_calloc(data->files_num + 1, sizeof(t_daft_list *));
	if (!data->data_list)
		return (_daft_log(DAFT_LOG_MALLOC));
	i = 0;
	while (i != data->files_num)
	{
		data->data_list[i] = ft_calloc(1, sizeof(t_daft_list));
		if (!data->data_list[i])
			return (_daft_log(DAFT_LOG_MALLOC));
		if (_daft_get_data(data->data_list[i], data->files_names[i], i) != 0)
			return (data->last_error);
		++i;
	}
	return (0);
}
