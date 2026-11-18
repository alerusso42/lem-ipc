/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 15:13:11 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/18 11:53:36 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem-ipc.h"

static void	_shm_init(t_proc *shared);
static void	_msgq_init(t_proc *data);
static int	_get_opt_index(const char *opt);
static void	_parse_argv(t_proc *data, char **argv);
static void	_parse_error(const char *opt, const char *msg);
static void	_parse_help(void);
static bool	_parse_toggle(const char *msg, const char *val);

/**
 * @brief setups the shared memory
 * 
 * @param data ptr to data
 */
void	setup(t_proc *data, char **argv)
{
	int	fd;
	int	n_client;

	*data = (t_proc){0};
	data->msg_fd = -1;
	_parse_argv(data, argv);
	//NOTE - if two processes becomes master, _shm_init handles it
	data->info.is_master = access("/dev/shm" SHM_FILE, F_OK) == -1;
	errno = 0;
	fd = shm_open(SHM_FILE, O_RDWR | O_CREAT, 0666);
	if (fd == -1)
		error(data, "shm_open failed");
	data->shared = mmap(NULL, sizeof(t_shared), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (data == (void *)-1)
		return (close(fd), error(data, "mmap failed"));
	if (ftruncate(fd, sizeof(t_shared)) != 0)
		return (close(fd), error(data, "ftruncate failed"));
	close(fd);
	if (data->info.is_master == true)
		_shm_init(data);
	_msgq_init(data);
	sem_wait(&data->shared->sem);
	if (data->info.is_master == false && data->shared->match.is_start == true)
		return (sem_post(&data->shared->sem), error(data, "Match is started"));
	n_client = ++data->shared->n_client;
	data->id = ++data->shared->id_count;
	sem_post(&data->shared->sem);
	debug_log_int(data, "Number of active clients: %d", n_client);
	if (!data->num_players)
		data->num_players = 4;
	if (data->info.is_master == false)
		msg_sendId(data, MSGID_FRONT, MSGE_CLIENT_NEW, NULL);
	debug_log_char(data, "%s matchmaking", data->info.is_master ? "start" : "join");
}

/**
 * @brief initialize shared memory and semaphore, if does not exist yet.\
 * 
 * an atomic variable checks that two masters cannot exist
 * 
 * @param data 
 */
static void	_shm_init(t_proc *data)
{
	char	is_init;

	is_init = ++data->shared->is_init;
	if (is_init != 1)
	{
		munmap(data->shared, sizeof(data->shared));
		shm_unlink(SHM_FILE);
		err_printf("two master detected.\n");
		exit(1);
	}
	if (sem_init(&data->shared->sem, 1, 1) != 0)
		error(data, "sem_init failed");
	data->shared->id_count = 1;//id 1 is reserved for SDL3 frontend
	debug_log(data, "$Yshared memory created..$Z");
}

//	usage of msgget taken from here
//https://stackoverflow.com/questions/49570961/message-queue-msgget-msgsnd-msgrcv-linux-eidrm
//https://stackoverflow.com/questions/7358400/whats-is-purpose-ftok-in-message-queues
static void	_msgq_init(t_proc *data)
{
	key_t			key;

	key = ftok(MSQ_FILE, 42);
	if (key < 0)
		return (error(data, "ftok"));
	data->msg_fd = msgget(key, IPC_CREAT | 0666);
	if (data->msg_fd < 0)
		return (error(data, "msgget"));
}

enum e_argv
{
	OPT_AI,
	OPT_SDL,
	OPT_TEAM,
	OPT_PLAYERS,
	OPT_HELP,
	OPT_USAGE,
	OPT_NUM	
};

#define PARSE_OPTIONS	\
(const char *[])\
{\
	[OPT_TEAM] 		= "--team=",\
	[OPT_PLAYERS]	= "--players=",\
	[OPT_AI]		= "--ai=",\
	[OPT_SDL]		= "--sdl=",\
	[OPT_HELP]		= "--help",\
	[OPT_USAGE]		= "--usage",\
	[OPT_NUM]		= "",\
}

#define PARSE_INSTRUCTIONS	\
(const char *[])\
{\
	[OPT_PLAYERS]	= "1-int_max [default: 1]",\
	[OPT_TEAM]		= "r/g/b/y : force the game to assign you a specific team",\
	[OPT_AI]		= "on/off [default: off]: if on, this process will be piloted by an AI",\
	[OPT_SDL]		= "on/off [default: on] enable/disable SDL",\
	[OPT_HELP]		= "show this message and exit",\
	[OPT_USAGE] 	= "show this message and exit",\
	[OPT_NUM]		= "",\
}

static void	_parse_argv(t_proc *data, char **argv)
{
	char	*val;
	int		len;
	int		opt_type;

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
			case (OPT_PLAYERS):
				data->num_players = ft_atoi(val);
				if (data->num_players <= 0)
					_parse_error(argv[i], "players usage: --players=x [0<x<int_max]");
				break ;
			case (OPT_HELP) : case (OPT_USAGE):
				_parse_help();
				break ;
			default :
				_parse_error(argv[i], "unrecognized flag (try --help)"); 
		}
	}
}

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

static void	_parse_error(const char *opt, const char *msg)
{
	err_printf("$RPARSING ERROR$Z\nInstruction: %s\n", opt);
	err_printf("Details: %s\n", msg);
	exit(1);
}

static void	_parse_help(void)
{
	ft_printf("Usage: \"./lem-ipc [optional flags]\"\n");
	ft_printf("Flags supported\n");
	for (int i = 0; i != OPT_NUM; i++)
		ft_printf("%s: %s\n", PARSE_OPTIONS[i], PARSE_INSTRUCTIONS[i]);
	exit(1);
}

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
