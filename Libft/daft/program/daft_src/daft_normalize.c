// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   daft_normalize.c                                   :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2026/03/22 18:16:08 by alerusso          #+#    #+#             */
// /*   Updated: 2026/03/25 16:48:02 by alerusso         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "daft_prog.h"

// static int		normalize_one(t_daft_data *data, t_daft_list *file, int enum_id);
// void			_daft_normalize_f(t_daft_data *dt, int i, char **line, void *norm);
// static t_str	*norm_str(t_daft_list *file, void *norm_data);

// int	daft_normalize(int enum_id)
// {
// 	t_daft_data	*data;
// 	int			exit_code;

// 	exit_code = 0;
// 	data = _daft_get_memory(NULL, false);
// 	if (!data)
// 		return (_daft_log(DAFT_LOG_NOMEM));
// 	if (enum_id < 0 || enum_id > data->files_num)
// 		return (_daft_log(DAFT_LOG_ENUM_ID));
// 	if (enum_id == data->files_num)
// 	{
// 		for (int i = 0; i != data->files_num; i++)
// 			exit_code += normalize_one(data, data->data_list[i], i);
// 	}
// 	else
// 		exit_code = normalize_one(data, data->data_list[enum_id], enum_id);
// 	if (exit_code != 0)
// 		return (exit_code);
// 	return (0);
// }

// static int	normalize_one(t_daft_data *data, t_daft_list *file, int enum_id)
// {
// 	char		*line;
// 	void		*norm_data;

// 	if (_daft_open_files(data, file->filename, data->conf.tmp_path))
// 		return (1);
// 	norm_data = get_normalize_data(file);
// 	if (!norm_data)
// 	{
// 		return (ft_printf("$Rno norm$Z\n\n"));
// 	}
// 	line = gnl();
// 	while (line)
// 	{
// 		if (*line != '#' && ft_strchr(line, file->field_sep))
// 			_daft_normalize_f(data, enum_id, &line, norm_data);
// 		else
// 		{
// 			tfd_printf(data->temp_files[1], "%s\n", line);
// 			FREE(line);
// 			line = gnl();
// 		}
// 	}
// 	rewrite_data(data, enum_id);
// 	return (closefd(data->temp_files[0]), closefd(data->temp_files[1]), 0);
// }

// static void	*get_normalize_data(t_daft_list *file)
// {
// 	void *norm_data;
// 	size_t	size;

// 	norm_data = daft_get("_NORM");
// 	return (norm_data);
// }
