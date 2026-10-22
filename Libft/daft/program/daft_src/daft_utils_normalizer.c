// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   daft_utils_normalizer.c                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2026/03/22 20:55:09 by alerusso          #+#    #+#             */
// /*   Updated: 2026/03/26 14:32:16 by alerusso         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "daft_prog.h"

// static void	str_handler(t_daft_data *dt, int i, char **line);
// static void	mtr_h_handler(t_daft_data *dt, int i, char **line, char **norm);
// static void	mtr_v_handler(t_daft_data *dt, int i, char **line, char **norm);
// static void	mtr_3d_handler(t_daft_data *dt, int i, char **line, char ***norm);

// void	_daft_normalize_f(t_daft_data *dt, int i, char **line, void *norm)
// {
// 	switch (_daft_find_data_type(dt->data_list[i]))
// 	{
// 		case (STRING) :
// 		{
// 			str_handler(dt, i, line);
// 			break ;
// 		}
// 		case (TWO_D_MATRIX) :
// 		{
// 			mtr_h_handler(dt, i, line, (char **)norm);
// 			break ;
// 		}
// 		case (TWO_D_MATRIX_VERTICAL) :
// 		{
// 			mtr_v_handler(dt, i, line, (char **)norm);
// 			break ;
// 		}
// 		case (THREE_D_MATRIX) :
// 		{
// 			mtr_3d_handler(dt, i, line, (char ***)norm);
// 		}
// 	}
// }

// //key value csv doesn't need any normalization
// static void	str_handler(t_daft_data *dt, int i, char **line)
// {
// 	tfd_printf(dt->temp_files[1], "%s\n", *line);
// 	FREE(*line);
// 	*line = gnl();
// }

// static void	mtr_h_handler(t_daft_data *dt, int i, char **line, char **norm)
// {
// 	int	norm_len;
// 	int	curr_len;

// 	norm_len = matrix2_len((char **)norm);
// 	curr_len = str_count(*line, dt->data_list[i]->field_sep);
// 	str_handler(dt, i, line);
// 	if (curr_len >= norm_len)
// 		return ;
// 	while (norm[curr_len])
// 	{
// 		tfd_printf(dt->temp_files[1], dt->data_list[i]->field_sep);
// 		tfd_printf(dt->temp_files[1], norm[curr_len]);
// 		curr_len++;
// 	}
// }

// static inline char	*get_key(void *data, int index, bool third_dim)
// {
// 	if (third_dim)
// 		return (((char ***)data)[index][0]);
// 	return (((char **)data)[index]);
// }

// static void	swap_fields(void *fields, void *norm, bool third_dim)
// {
// 	int		j;
// 	int		key_len;
// 	t_list	*fields;
// 	t_list	*curr;

// 	j = 0;
// 	fields = lst_new(*fields);
// 	if (!fields)
// 		return ;
// 	curr = fields;
// 	while ((*fields)[j] && ft_strchr(*fields, *dt->data_list[i]->field_sep))
// 	{
// 		(*fields)[sub_strlen(*fields, dt->data_list[i]->field_sep, EXCLUDE)] = 0;
// 		curr->next = lst_new(*fields);
// 		curr = curr->next;
// 		*fields = gnl();
// 		++j;
// 	}
// 	curr = fields;
// 	j = 0;
// 	while (fields[j])
// 	{
// 		key_len = sub_strlen(curr->content, dt->data_list[i]->field_sep, EXCLUDE);
// 		if (ft_strncmp(curr->content, norm[j], key_len) != 0)
// 			swap_fields(fields, curr, key_len, norm[j]);
// 		else
// 		{
// 			((char *)(curr->content))[key_len] = *dt->data_list[i]->field_sep;
// 			tfd_printf(dt->temp_files[1], "%s\n", fields->content);
// 			if (curr == fields)
// 				fields = fields->next;
// 			lst_delone(curr, FREE);
// 		}
// 	}
// 	lst_clear(&fields, NULL);
// }

// static void	mtr_v_handler(t_daft_data *dt, int i, char **line, char **norm)
// {
// 	char	**matr;
// 	int		j;

// 	str_handler(dt, i, line);
// 	matr = _daft_get_vertical_matr(dt, dt->data_list[i]);
// 	if (!matr)
// 		return ;
// 	swap_fields((void *)matr, (void *)norm, false);
// 	j = 0;
// 	tfd_printf(dt->temp_files[1], "%s%s", matr[0], dt->data_list[i]->field_sep);
// 	while (matr[j])
// 	{
// 		tfd_printf(dt->temp_files[1], "%s", matr[1]);
// 		if (matr[j + 1])
// 			tfd_printf(dt->temp_files[1], "%s", dt->data_list[i]->values_sep);
// 		++j;
// 	}
// }

// static void	mtr_3d_handler(t_daft_data *dt, int i, char **line, char ***norm)
// {
// 	char	***matr;
// 	int		j;
// 	int		k;

// 	str_handler(dt, i, line);
// 	matr = _daft_get_three_d_matr(dt, dt->data_list[i]);
// 	if (!matr)
// 		return ;
// 	swap_fields((void *)matr, (void *)norm, false);
// 	k = 0;
// 	while ()
// 	j = 0;
// 	tfd_printf(dt->temp_files[1], "%s%s", matr[k][0], dt->data_list[i]->field_sep);
// 	while (matr[j])
// 	{
// 		tfd_printf(dt->temp_files[1], "%s", matr[k][j]);
// 		if (matr[j + 1])
// 			tfd_printf(dt->temp_files[1], "%s", dt->data_list[i]->values_sep);
// 		++j;
// 	}
// }
