/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:03:56 by alerusso          #+#    #+#             */
/*   Updated: 2026/01/06 12:53:14 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H
# include "ft_printf_data.h"

# define FUNC_CAST(...)	(void(*)(__VA_ARGS__))

enum	e_ft_printf_func
{
	VOID = 0,
	INT1 = 1 << 0,
	INT2 = 1 << 1,
	INT3 = 1 << 2,
	PTR1 = 1 << 3,
	PTR2 = 1 << 4,
	PTR3 = 1 << 5,
};

#endif