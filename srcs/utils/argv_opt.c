/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_opt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 15:50:18 by alerusso42        #+#    #+#             */
/*   Updated: 2026/11/27 14:53:04 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem-ipc.h"

static int	_get_opt_index(const char *opt);
static void	_parse_error(const char *opt, const char *msg);
static void	_parse_help(void);
static bool	_parse_toggle(const char *msg, const char *val);

enum e_argv
{
	OPT_AI,
	OPT_SDL,
	OPT_TEAM,
	OPT_N_TEAM,
	OPT_PLAYERS,
	OPT_HELP,
	OPT_USAGE,
	OPT_NUM	
};

#define PARSE_OPTIONS	\
(const char *[])\
{\
	[OPT_AI]		= "--ai=",\
	[OPT_SDL]		= "--sdl=",\
	[OPT_TEAM] 		= "--team=",\
	[OPT_PLAYERS]	= "--players=",\
	[OPT_HELP]		= "--help",\
	[OPT_USAGE]		= "--usage",\
	[OPT_N_TEAM]	= "--nteam=",\
	[OPT_NUM]		= "",\
}

#define PARSE_INSTRUCTIONS	\
(const char *[])\
{\
	[OPT_PLAYERS]	= "1-int_max [default: 1]",\
	[OPT_TEAM]		= "r/g/b/y : force the game to assign you a specific team",\
	[OPT_N_TEAM] 	= "1/2/3/4 : [default: 4] choose the number of teams",\
	[OPT_AI]		= "on/off [default: off]: if on, this process will be piloted by an AI",\
	[OPT_SDL]		= "on/off [default: on] enable/disable SDL",\
	[OPT_HELP]		= "show this message and exit",\
	[OPT_USAGE] 	= "show this message and exit",\
	[OPT_NUM]		= "",\
}

/**
 * @brief parse argv options, with --opt=value format
 * 
 * @param data 
 * @param argv 
 */
void	parse_argv(t_proc *data, char **argv)
{
	char	*val;
	int		len;
	int		opt_type;
	int64_t	n;

	for (int i = 1; argv[i] != NULL; i++)
	{
		opt_type = _get_opt_index(argv[i]);
		len = ft_strlen(PARSE_OPTIONS[opt_type]);
		val = argv[i] + len;
		switch (opt_type)
		{
			case (OPT_AI):
				if (_parse_toggle(argv[i], val) == true)
					data->info.is_ai = true;
				break ;
			case (OPT_SDL):
				if (_parse_toggle(argv[i], val) == false)
					data->info.is_sdl_disabled = true;
				break ;
			case (OPT_TEAM):
				if (*val == 'r' || *val == 'R')
					data->info.team = INFO_TEAM_RED;
				else if (*val == 'g' || *val == 'G')
					data->info.team = INFO_TEAM_GREEN;
				else if (*val == 'b' || *val == 'B')
					data->info.team = INFO_TEAM_BLUE;
				else if (*val == 'y' || *val == 'Y')
					data->info.team = INFO_TEAM_YELLOW;
				else
					_parse_error(argv[i], "team usage: --team=r/g/b/y");
				data->info.is_team_lock = true;
				break ;
			case (OPT_N_TEAM):
				n = ft_atoi(val);
				if (n < 0)
					_parse_error(argv[i], "Ahhh, yes. Negative teams.\nSegmentation Fault\nAre you happy now? You wanted this, or not??? Go to hell.");
				else if (n == 0)
					_parse_error(argv[i], "Look, I get you like silence, but.. whatever.");
				else if (n > 4)
					_parse_error(argv[i], "Sadly, the max number of teams is 4. Try asking a patch.");
				else if (n > 100)
					_parse_error(argv[i], "Wow, dude. You know very big numbers. Well done!");
				else if (n == INT_MAX)
					_parse_error(argv[i], "I like that number too!");
				data->info.num_team = (uint8_t)n;
				break ;
			case (OPT_PLAYERS):
				n = ft_atoi(val);
				if (n <= 0)
					_parse_error(argv[i], "players usage: --players=x [0<x<int_max]");
				data->min_players = n;
				break ;
			case (OPT_HELP) : case (OPT_USAGE):
				_parse_help();
				break ;
			default :
				_parse_error(argv[i], "unrecognized flag (try --help)"); 
		}
	}
	if (!data->info.num_team)
		data->info.num_team = INFO_TEAM_NUM;
	if (!data->min_players)
		data->min_players = data->info.num_team;	
}

//strcmp a char * opt to return the int index
static int	_get_opt_index(const char *opt)
{
	int	opt_len;

	for (int i = 0; i != OPT_NUM; i++)
	{
		opt_len = sub_strlen(PARSE_OPTIONS[i], "=", EXCLUDE);
		if (ft_strncmp(opt, PARSE_OPTIONS[i], opt_len))
			continue ;
		return (i);
	}
	return (OPT_NUM);
}

//used when an opt or its value are wrong
static void	_parse_error(const char *opt, const char *msg)
{
	err_printf("$RPARSING ERROR$Z\nInstruction: %s\n", opt);
	err_printf("Details: %s\n", msg);
	exit(1);
}

//show a help message
static void	_parse_help(void)
{
	ft_printf("Usage: \"./lem-ipc [optional flags]\"\n");
	ft_printf("Flags supported\n");
	for (int i = 0; i != OPT_NUM; i++)
		ft_printf("$B%s$Z: %s\n", PARSE_OPTIONS[i], PARSE_INSTRUCTIONS[i]);
	exit(0);
}

//used to toggle on/off opt
static bool	_parse_toggle(const char *opt, const char *val)
{
	if (ft_strncmp(val, "on", 2) == 0)
		return (true);
	else if (ft_strncmp(val, "off", 3) == 0)
		return (false);
	else
		_parse_error(opt, "usage: on/off");
	return (false);
}
