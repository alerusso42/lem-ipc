/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 15:13:11 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/17 13:41:41 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/backend.h"

static void	_shm_init(t_proc *shared);
static void	_msgq_init(t_proc *data);
static int	_get_opt_index(const char *opt);
static void	_parse_argv(t_proc *data, char **argv);
static void	_parse_error(const char *opt, const char *msg);
static void	_parse_help(void);

/**
 * @brief setups the shared memory
 * 
 * @param data ptr to data
 */
void	setup(t_proc *data, char **argv)
{
	int	fd;

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
	ft_printf("Number of active clients: %d\n", ++data->shared->n_client);
	data->id = ++data->shared->id_count;
	sem_post(&data->shared->sem);
	msg_sendId(data, 1, MSGE_CLIENT_NEW, NULL);
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
	ft_printf("$Yshared memory created..$Z\n");
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
	OPT_HELP,
	OPT_USAGE,
	OPT_NUM	
};

#define PARSE_OPTIONS	\
(const char *[])\
{\
	[OPT_TEAM] = "--team=",\
	[OPT_AI] = "--ai=",\
	[OPT_SDL] = "--sdl=",\
	[OPT_HELP] = "--help",\
	[OPT_USAGE] = "--usage",\
	[OPT_NUM] = NULL,\
}

static void	_parse_argv(t_proc *data, char **argv)
{
	char	*val;

	for (int i = 1; argv[i] != NULL; i++)
	{
		switch (_get_opt_index(argv[i]))
		{
			case (OPT_AI):
				data->info.is_ai = true;
				break ;
			case (OPT_SDL):
				data->info.is_sdl_disabled = true;
				break ;
			case (OPT_TEAM):
				val = argv[i] + ft_strlen(PARSE_OPTIONS[OPT_TEAM]);
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
	err_printf("Valid flags are: %s\n", msg);
	exit(1);
}

static void	_parse_help(void)
{
	ft_printf("Usage: \"./lem-ipc [optional flags]\"\n");
	ft_printf("Flags supported\n");
	for (int i = 0; i != OPT_NUM; i++)
		ft_printf("%s\n", PARSE_OPTIONS[i]);
	exit(1);
}
