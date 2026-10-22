/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft_utils_edit3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:31:20 by alerusso          #+#    #+#             */
/*   Updated: 2026/01/05 17:43:04 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "daft_prog.h"

static void	str_handler(t_daft_data *dt, int i, char **line, char *mem);
static void	mtr_h_handler(t_daft_data *dt, int i, char **line, char **mem);
static void	mtr_v_handler(t_daft_data *dt, int i, char **line, char **mem);
static void	mtr_3d_handler(t_daft_data *dt, int i, char **line, char ***mem);

void	_daft_edit_f(t_daft_data *dt, int i, char **line, t_daft_mem *mem)
{
	switch (_daft_find_data_type(dt->data_list[i]))
	{
		case (STRING) :
		{
			str_handler(dt, i, line, (char *)mem->ptr);
			break ;
		}
		case (TWO_D_MATRIX) :
		{
			mtr_h_handler(dt, i, line, (char **)mem->ptr);
			break ;
		}
		case (TWO_D_MATRIX_VERTICAL) :
		{
			mtr_v_handler(dt, i, line, (char **)mem->ptr);
			break ;
		}
		case (THREE_D_MATRIX) :
		{
			mtr_3d_handler(dt, i, line, (char ***)mem->ptr);
		}
	}
	_daft_free_mem(dt, dt->mem.add);
}

static void	str_handler(t_daft_data *dt, int i, char **line, char *mem)
{
	int		len;

	if (**line == '#' || !ft_strchr(*line, *dt->data_list[i]->key_value_sep))
	{
		(void)tfd_printf(dt->temp_files[1], "%s\n", *line);
		FREE(*line);
		*line = gnl();
		return ;
	}
	len = sub_strlen(*line, dt->data_list[i]->key_value_sep, EXCLUDE);
	writefd(dt->temp_files[1], *line, len + 1);
	tfd_printf(dt->temp_files[1], "%s\n", mem);
	FREE(*line);
	*line = gnl();
}

static void	mtr_h_handler(t_daft_data *dt, int i, char **line, char **mem)
{
	int		len;
	int		j;

	if (**line == '#' || !ft_strchr(*line, *dt->data_list[i]->key_value_sep))
	{
		(void)tfd_printf(dt->temp_files[1], "%s\n", *line);
		FREE(*line);
		*line = gnl();
		return ;
	}
	len = sub_strlen(*line, dt->data_list[i]->key_value_sep, EXCLUDE);
	writefd(dt->temp_files[1], *line, len + 1);
	j = 0;
	while (mem[j])
	{
		tfd_printf(dt->temp_files[1], "%s", mem[j]);
		++j;
		if (mem[j - 1][0] && mem[j] && mem[j][0])
			tfd_printf(dt->temp_files[1], "%c", *dt->data_list[i]->values_sep);
	}
	tfd_printf(dt->temp_files[1], "\n");
	FREE(*line);
	*line = gnl();
}

static void	mtr_v_handler(t_daft_data *dt, int i, char **line, char **mem)
{
	int		j;

	tfd_printf(dt->temp_files[1], "%s\n", *line);
	FREE(*line);
	*line = gnl();
	j = 0;
	while (mem[j] && mem[j][0] && !ft_strchr(*line, *dt->data_list[i]->field_sep))
	{
		str_handler(dt, i, line, mem[j]);
		++j;
	}
}

static void	mtr_3d_handler(t_daft_data *dt, int i, char **line, char ***mem)
{
	int		j;

	tfd_printf(dt->temp_files[1], "%s\n", *line);
	FREE(*line);
	*line = gnl();
	j = 0;
	while (mem[j] && !ft_strchr(*line, *dt->data_list[i]->field_sep))
	{
		mtr_h_handler(dt, i, line, mem[j]);
		++j;
	}
}
