/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 09:27:35 by alerusso          #+#    #+#             */
/*   Updated: 2026/04/25 15:45:43 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_data.h"

static void	type_print(t_ft_printf *data);
static void	ansi_print(t_ft_printf *data);
static void	exec_cmd(t_ft_printf *data);


int	_ft_printf(int fd, const char *str, t_str *buff, va_list *ptr)
{
	t_ft_printf	data;

	if (!str || !ptr || (fd == -1 && !buff))
		return (0);
	data = (t_ft_printf){0};
	data.buff = buff;
	data.args = ptr;
	data.s = str;
	data.fd = fd;
	while (*data.s != '\0')
	{
		if (*data.s == '%')
			type_print(&data);
		else if (*data.s == '$')
			ansi_print(&data);
		else if (*data.s == '?')
			exec_cmd(&data);
		else
		{
			print_char(&data, *data.s);
			data.s++;
		}
	}
	return (data.len);
}

static void	type_print(t_ft_printf *data)
{
	data->s++;
	switch (*data->s)
	{
		case 'c' :
			print_char(data, (char)va_arg(*data->args, int));
			break ;
		case 's' :
			print_str(data, (char *)va_arg(*data->args, char *));
			break ;
		case 'd' :
			print_int(data, (int)va_arg(*data->args, int64_t));
			break ;
		case 'u' :
			print_uint(data, (int)va_arg(*data->args, uint64_t));
			break ;
		case 'p' :
			print_uint(data, (int)va_arg(*data->args, uint64_t));
			break ;
		case '%' :
			print_char(data, '%');
			break ;
		default :
			return (print_str(data, "/UNKNOWN TYPE/"));
	}
	data->s++;
}

static void	ansi_print(t_ft_printf *data)
{
	static const uint8_t	ansi_table['~' - ' '] = FT_PRINTF_ANSI_TABLE;
	uint8_t					ansi_flags;
	char					result[MAX_ANSI_SIZE];
	int						len;
	uint8_t					ansi_type;

	PRINTF_DEBUG("\033[32mPRINTF_DEBUG\033[0m: cursor: %s\n", data->s);
	data->s++;
	if (*data->s == '$')
		return (print_char(data, '$'), data->s++, (void)0);
	if (*data->s < 32)
		return ;
	ansi_type = ansi_table[(int)*data->s - ' '];
	if (ansi_type == 255)
		return (_error(data, "/UNKNOWN ANSICODE/", 19));
	ansi_flags = 0;
	if (ft_isalnum(*data->s) == false)
		ansi_flags |= ANSI_ARGS;
	else if (ft_isalpha(*data->s) == true)
		ansi_flags |= ANSI_M_SEPARATOR;
	data->s++;
	len = ansi_fill(data, ansi_flags, ansi_type, result);
	print_str_len(data, result, len);
	data->len -= len;
	*result = '\\';
	PRINTF_DEBUG("\033[31mPRINTF_DEBUG\033[0m: ansi result: %s\n", result);
}

static void	exec_cmd(t_ft_printf *data)
{
	void	*f;
	void	*ptr_args[3];
	int64_t	val_args[3];

	PRINTF_DEBUG("\033[32mPRINTF_DEBUG\033[0m: cmd: %s\n", data->s);
	data->s++;
	if (*data->s == '?')
		return (print_char(data, *data->s++));
	if (data->s[0] != '%' || data->s[1] != 'p')
		return ;
	f = va_arg(*data->args, void *);
	data->s += 2;
	if (*data->s != '-' && *data->s != '?')
		return (_error(data, "/MISSING -/", 12));
	run_cmd(data, f, ptr_args, val_args);
	if (*data->s)
		data->s++;
}
