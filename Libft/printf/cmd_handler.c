/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:23:54 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 13:46:13 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_data.h"

static void	select_proto(t_ft_printf *data, void *f, void **ptr, int64_t *val);
static void	cmd_get_arg(t_ft_printf *data, void **ptr, int64_t *val, int cmd);
static void	cmd_get_val(t_ft_printf *data, int64_t *val, int cmd);
static void	cmd_get_str(t_ft_printf *data, void **ptr, t_str **arr, int cmd);

void	run_cmd(t_ft_printf *data, void *f, void **ptr_args, int64_t *val_args)
{
	STR(s1, NULL);
	STR(s2, NULL);
	STR(s3, NULL);
	t_str	*str_array[3] = {&s1, &s2, &s3};
	int		cmd_counter;

	data->cmd_flags = 0;
	cmd_counter = -1;
	while (++cmd_counter != 3 && *data->s && *data->s != '?')
	{
		++data->s;
		if (*data->s == '%')
			cmd_get_arg(data, ptr_args, val_args, cmd_counter);
		else if (ft_isdigit(*data->s))
			cmd_get_val(data, val_args, cmd_counter);
		else
			cmd_get_str(data, ptr_args, str_array, cmd_counter);
		data->s += sub_strlen(data->s, "-?", EXCLUDE);
	}
	if (!*data->s)
		return ;
	if (cmd_counter == 3)
		return (print_str_len(data, "/CMD ACCEPTS MAX 3 ARGS/", 25));
	select_proto(data, f, ptr_args, val_args);
}

static void	select_proto(t_ft_printf *data, void *f, void **ptr, int64_t *val)
{
	switch (data->cmd_flags)
	{
		case (VOID) ://SECTION - no args
			return ((FUNC_CAST()f)());
		case (INT1) ://SECTION - only int
			return ((FUNC_CAST(int)f)(val[0]));
		case (INT1 | INT2) :
			return ((FUNC_CAST(int, int)f)(val[0], val[1]));
		case (INT1 | INT2 | INT3) :
			return ((FUNC_CAST(int, int, int)f)(val[0], val[1], val[2]));
		case (PTR1) ://SECTION - only ptr
			return ((FUNC_CAST(void*)f)(ptr[0]));
		case (PTR1 | PTR2) :
			return ((FUNC_CAST(void*, void*)f)(ptr[0], ptr[1]));
		case (PTR1 | PTR2 | PTR3) :
			return ((FUNC_CAST(void*, void*, void*)f)(ptr[0], ptr[1], ptr[2]));
		case (INT1 | PTR2) ://SECTION - couple
			return ((FUNC_CAST(int, void*)f)(val[0], ptr[1]));
		case (PTR1 | INT2) :
			return ((FUNC_CAST(void*, int)f)(ptr[0], val[1]));
		case (INT1 | PTR2 | PTR3) ://SECTION - int as first arg
			return ((FUNC_CAST(int, void*, void*)f)(val[0], ptr[1], ptr[2]));
		case (INT1 | INT2 | PTR3) :
			return ((FUNC_CAST(int, int, void*)f)(val[0], val[1], ptr[2]));
		case (INT1 | PTR2 | INT3) :
			return ((FUNC_CAST(int, void*, int)f)(val[0], ptr[1], val[2]));
		case (PTR1 | INT2 | INT3) ://SECTION - ptr as first arg
			return ((FUNC_CAST(void*, int, int)f)(ptr[0], val[1], val[2]));
		case (PTR1 | INT2 | PTR3) :
			return ((FUNC_CAST(void*, int, void*)f)(ptr[0], val[1], ptr[2]));
		case (PTR1 | PTR2 | INT3) :
			return ((FUNC_CAST(void*, void*, int)f)(ptr[0], ptr[1], val[2]));
		default: 
			return (_error(data, "/CMD PROTO NOT FOUND/", 22));			
	}
}

static void	cmd_get_arg(t_ft_printf *data, void **ptr, int64_t *val, int cmd)
{
	char	type;

	type = data->s[1];
	data->s += 2;
	if (type != 'd' && type != 'p')
		return (_error(data, "/CMD ARG ACCEPTS d AND p ONLY/", 31));
	if (type == 'd')
	{
		val[cmd] = va_arg(*data->args, int64_t);
		data->cmd_flags |= INT1 << cmd;
	}
	else
	{
		ptr[cmd] = va_arg(*data->args, void *);
		data->cmd_flags |= PTR1 << cmd;
	}
}

static void	cmd_get_val(t_ft_printf *data, int64_t *val, int cmd)
{
	val[cmd] = ft_atoi(data->s);
	data->cmd_flags |= INT1 << cmd;
}

static void	cmd_get_str(t_ft_printf *data, void **ptr, t_str **arr, int cmd)
{
	str_excpy(arr[cmd], data->s, "-?");
	ptr[cmd] = (void *)arr[cmd]->buff;
	data->cmd_flags |= PTR1 << cmd;
}
