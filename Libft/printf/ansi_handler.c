/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:58:05 by alerusso          #+#    #+#             */
/*   Updated: 2026/01/05 20:39:44 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_data.h"

static int	ansi_get_arg(t_ft_printf *data, char *arg)
{
	int	n;
	int	size;

	if (!ft_isdigit(*data->s) && *data->s != '%')
		return (0);
	if (*data->s == '%')
	{
		if (data->s[1] == 'd' || data->s[1] == 'u')
			n = (int)va_arg(*data->args, int);
		else
			return (0);
		data->s += 2;
		size = int_size(n);
	}
	else
	{
		n = ft_atoi(data->s);
		size = int_size(n);
		data->s += size + (n < 0);
	}
	if (size < MAX_ANSI_ARG && n > 0)
		ft_itoa_stack(arg, n);
	return (size);
}

int		ansi_fill(t_ft_printf *data, uint32_t flags, uint8_t type, char *res)
{
	char	type_buffer[3];
	int		i;

	type_buffer[0] = (char)type;
	type_buffer[1] = 0;
	i = 2;// ESC + [
	ft_strlcpy(res, "\033[", i + 1);
	if (flags & ANSI_M_SEPARATOR && type >= '0' && type <= '9')
		res[i++] = type;
	else if (flags & ANSI_M_SEPARATOR)
	{
		ft_itoa_stack(res + i, type);
		i += int_size(type);
	}
	if (flags & ANSI_ARGS)
		i += ansi_get_arg(data, res + i);
	if (i >= MAX_ANSI_SIZE)
		return (i);
	res[i] = 0;
	if (flags & ANSI_M_SEPARATOR)
		ft_strlcpy(res + i++, "m", 2);
	else
		ft_strlcpy(res + i++, type_buffer, 2);
	return (i);
}
