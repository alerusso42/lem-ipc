/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 09:28:04 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/18 11:41:10 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem-ipc.h"

static bool	_make_base_str(t_proc *proc, const char *msg, t_str **str);

void	debug_log(t_proc *proc, const char *msg)
{
	t_str	*str;

	if (_make_base_str(proc, msg, &str) == false)
		return ;
	ft_printf(str->buff);
	str = str_delete(str);
}

void	debug_log_int(t_proc *proc, const char *msg, int n)
{
	t_str	*str;

	if (_make_base_str(proc, msg, &str) == false)
		return ;
	ft_printf(str->buff, n);
	str = str_delete(str);
}

void	debug_log_char(t_proc *proc, const char *msg, const char *s)
{
	t_str	*str;

	if (_make_base_str(proc, msg, &str) == false)
		return ;
	ft_printf(str->buff, s);
	str = str_delete(str);
}

void	debug_log_int_char(t_proc *proc, const char *msg, int n, const char *s)
{
	t_str	*str;

	if (_make_base_str(proc, msg, &str) == false)
		return ;
	ft_printf(str->buff, n, s);
	str = str_delete(str);
}

static bool	_make_base_str(t_proc *proc, const char *msg, t_str **ptr)
{
	if (str_new(ptr, "") != 0)
		return (false);
	if (proc->id == 0)
		str_printf(*ptr, "[SETUP]: %s\n", msg);
	else if (proc->id == MSGID_FRONT)
		str_printf(*ptr, "[FRONT]: %s\n", msg);
	else if (proc->id == MSGID_MASTER && proc->shared->match.is_start == false)
		str_printf(*ptr, "[CHIEF]: %s\n", msg);
	else
		str_printf(*ptr, "[CLI %d]: %s\n", proc->id, msg);
	if ((*ptr)->err != 0)
		return (str_delete(*ptr), false);
	return (true);
}
