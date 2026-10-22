/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft_utils_settings.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:50:14 by alerusso          #+#    #+#             */
/*   Updated: 2026/01/02 11:22:51 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prog.h"

static int	parse_config(t_daft_data *data, char *line);

//	Checks for settings in all lines that are not comments.
//	Stop when finding an empty line after the first setting found.
int	_daft_save_config(t_daft_data *data)
{
	bool	found_first;
	char	*line;

	found_first = false;
	line = gnl();
	while (line)
	{
		if (found_first && !line[0])
		{
			FREE(line);
			break ;
		}
		else if (!ft_strchr("#", line[0]))
		{
			found_first = true;
			if (parse_config(data, line) != 0)
			{
				FREE(line);
				break ;
			}
		}
		FREE(line);
		line = gnl();
	}
	return (0);
}

//	List of all general config.
static int	parse_config(t_daft_data *data, char *line)
{
	if (!ft_strncmp(line, "DEFAULT_FLAGS->", 15))
	{
		data->conf.default_flags = ft_strdup(line + 15);
		if (!data->conf.default_flags)
			return (_daft_log(DAFT_LOG_MALLOC));
	}
	else if (!ft_strncmp(line, "DEBUG_LOG->", 11))
	{
		if (line[11] == 'y')
			data->conf.debug_log = true;
	}
	return (0);
}

static char	*cut_flag(char *flag);

char	*_daft_get_flags(t_daft_data *data, int fnum)
{
	char	*line;
	bool	start_count;
	t_fd	sett_fd;

	start_count = false;
	sett_fd = openfd(data->conf.sett_path, "r");
	if (!sett_fd.n)
		return (_daft_log(DAFT_LOG_SETT), NULL);
	line = gnl();
	while (line)
	{
		if (!ft_strncmp(line, "# -- FLAGS -- #", 15))
			start_count = true;
		FREE(line);
		line = gnl();
		if (start_count == true && fnum-- == 0)
			break ;
	}
	closefd(sett_fd);
	if (!line)
		return (NULL);
	return (cut_flag(line));
}

static char	*cut_flag(char *flag)
{
	int		i;

	i = sub_strlen(flag, ">", EXCLUDE);
	if (!flag[i])
		return (FREE(flag), NULL);
	cut_string(flag, 0, i + 1);
	return (flag);
}
