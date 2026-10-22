/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_data.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:11:37 by alerusso          #+#    #+#             */
/*   Updated: 2026/01/06 12:41:41 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_DATA
# define FT_PRINTF_DATA
# include "ft_printf.h"
# include "ansicode.h"
# include "commands.h"
# define MAX_NUMBER_SIZE 21
# define MAX_ANSI_ARG 4
# define MAX_ANSI_SIZE (4 + MAX_ANSI_ARG) // ESC[9999A
# define FT_PRINTF_DEBUG false
# if FT_PRINTF_DEBUG
#  define PRINTF_DEBUG(str, ...)	ft_printf(str, ##__VA_ARGS__)
# else
#  define PRINTF_DEBUG(str, ...)	(void)0
#endif

typedef struct s_ft_printf	t_ft_printf;

void	print_str(t_ft_printf *data, char *s);
void	print_str_len(t_ft_printf *data, char *s, int len);
void	print_char(t_ft_printf *data, char c);
void	print_int(t_ft_printf *data, int64_t n);
void	print_uint(t_ft_printf *data, uint64_t n);

void	_error(t_ft_printf *data, char *err, int err_len);

int		ansi_fill(t_ft_printf *data, uint32_t flags, uint8_t type, char *res);
void	run_cmd(t_ft_printf *data, void *f, void **ptr_args, int64_t *val_args);

//int fd, const char *str, t_str *buff, va_list *ptr
typedef struct s_ft_printf
{
	t_str		*buff;
	va_list		*args;
	const char	*s;
	int			fd;
	int			len;
	uint8_t		cmd_flags;
}	t_ft_printf;

#endif