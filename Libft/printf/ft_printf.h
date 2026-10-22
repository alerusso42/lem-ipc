/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:16:24 by codespace         #+#    #+#             */
/*   Updated: 2026/10/02 13:54:27 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include "../string/string.h"

typedef struct s_str t_str;
typedef struct s_fd t_fd;

void	ft_putchar_fd(char c, t_fd fd);
void	ft_putendl_fd(char *s, t_fd fd);
void	ft_putnbr_fd(int n, t_fd fd);
void	ft_putstr_fd(char *s, t_fd fd);
int		tfd_printf(t_fd fd, const char *str, ...);
int		fd_printf(int fd, const char *str, ...);
int	    ft_printf(const char *str, ...);
int		err_printf(const char *str, ...);
int		str_printf(t_str *buff, const char *str, ...);

#endif