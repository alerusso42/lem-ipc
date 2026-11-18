/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 09:28:04 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/18 19:14:27 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem-ipc.h"
#define RED		"$R"
#define RESET	"$Z"
#define EMPTY	""

static bool	_print_start(t_proc *proc, const char *msg, t_str **str);
static void	_print_end(t_proc *proc, t_str **ptr);

void	debug_log(t_proc *proc, const char *msg)
{
	t_str	*str;

	if (_print_start(proc, msg, &str) == false)
		return ;
	ft_printf(str->buff);
	_print_end(proc, &str);
}

void	debug_log_int(t_proc *proc, const char *msg, int n)
{
	t_str	*str;

	if (_print_start(proc, msg, &str) == false)
		return ;
	ft_printf(str->buff, n);
	_print_end(proc, &str);
}

void	debug_log_char(t_proc *proc, const char *msg, const char *s)
{
	t_str	*str;

	if (_print_start(proc, msg, &str) == false)
		return ;
	ft_printf(str->buff, s);
	_print_end(proc, &str);
}

void	debug_log_char_char(t_proc *proc, const char *msg, const char *s1, const char *s2)
{
	t_str	*str;

	if (_print_start(proc, msg, &str) == false)
		return ;
	ft_printf(str->buff, s1, s2);
	_print_end(proc, &str);
}

void	debug_log_int_char(t_proc *proc, const char *msg, int n, const char *s)
{
	t_str	*str;

	if (_print_start(proc, msg, &str) == false)
		return ;
	ft_printf(str->buff, n, s);
	_print_end(proc, &str);
}

static bool	_print_start(t_proc *proc, const char *msg, t_str **ptr)
{
	char	*red;
	char	*reset;
	bool	is_match_start;

	if (str_new(ptr, "") != 0)
		return (false);
	red = EMPTY;
	reset = EMPTY;
	is_match_start = proc->shared && proc->shared->match.is_start;
	if (proc->info.error == true)
	{
		red = RED;
		reset = RESET;
	}
	if (proc->id == 0)
		str_printf(*ptr, "%s[SETUP]%s: %s\n", red, reset, msg);
	else if (proc->id == MSGID_FRONT)
		str_printf(*ptr, "%s[FRONT]%s: %s\n", red, reset, msg);
	else if (proc->id == MSGID_MASTER && is_match_start == false)
		str_printf(*ptr, "%s[CHIEF]%s: %s\n", red, reset, msg);
	else if (proc->info.is_id_ok == false)
		str_printf(*ptr, "%s[CLI ????]%s: %s\n", red, reset, msg);
	else
		str_printf(*ptr, "%s[CLI %d]%s: %s\n", red, proc->id, reset, msg);
	if ((*ptr)->err != 0)
		return (str_delete(*ptr), false);
	if (proc->shared)
		sem_wait(&proc->shared->s_print);
	return (true);
}

static void	_print_end(t_proc *proc, t_str **ptr)
{
	if (proc->shared)
		sem_post(&proc->shared->s_print);
	*ptr = str_delete(*ptr);
}
