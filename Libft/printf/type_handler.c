/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:33:05 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/01 13:51:20 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_data.h"

void	print_char(t_ft_printf *data, char c)
{
	if (!c)
		return ;
	data->len++;
	if (data->fd < 0)
		str_addr(data->buff, c);
	else
		WRITE(data->fd, &c, 1);
}

void	print_str(t_ft_printf *data, char *s)
{
	int	len;

	if (s == NULL)
		return (print_str(data, "(NULL)"));
	len = ft_strlen(s);
	if (data->fd < 0)
		str_push(data->buff, s);
	else
		WRITE(data->fd, s, len);
	data->len += len;
}

void	print_str_len(t_ft_printf *data, char *s, int len)
{
	if (s == NULL)
		return (print_str(data, "(NULL)"));
	if (data->fd < 0)
		str_push(data->buff, s);
	else
		WRITE(data->fd, s, len);
	data->len += len;
}

void	print_int(t_ft_printf *data, int64_t n)
{
	char	n_buff[MAX_NUMBER_SIZE];

	ft_itoa_stack(n_buff, (int64_t)n);
	print_str(data, n_buff);
}

void	print_uint(t_ft_printf *data, uint64_t n)
{
	char	n_buff[MAX_NUMBER_SIZE];

	ft_uitoa_stack(n_buff, (uint64_t)n);
	print_str(data, n_buff);
}
