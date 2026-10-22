/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft_prog.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 21:56:13 by alerusso          #+#    #+#             */
/*   Updated: 2026/01/16 22:01:07 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAFT_PROG_H
# define DAFT_PROG_H
# include "../../daft.h"
# include "../prep_src/daft_prep.h"

# define SEED 42

typedef struct s_daft_data	t_daft_data;
typedef struct s_daft_conf	t_daft_conf;
typedef struct s_daft_mem	t_daft_mem;
typedef struct s_daft_list	t_daft_list;
typedef struct s_daft_node	t_daft_node;
typedef unsigned int		t_bool;

struct s_daft_conf
{
	char	*default_flags;
	char	*path;
	char	*sett_path;
	char	*tmp_path;
	char	*log_path;
	t_bool	debug_log;
};

struct s_daft_mem
{
	t_daft_mem		*next;
	void			*ptr;
	char			*key;
	int				file;
	int				offset;
	int				hash;
	char			type;
	t_bool			add:1;
};

struct s_daft_data
{
	t_daft_conf	conf;
	t_daft_mem	mem;
	t_daft_mem	*old_mem;
	t_fd		log_file;
	t_fd		temp_files[2];
	t_daft_list	**data_list;
	char		**files_names;
	char		*error_message;
	int			files_num;
	int			current_file;
	int			mem_size;
	int			last_error;
	int			minimal_alloc_size;
	int			minimal_matrix_num;
};

struct s_daft_list
{
	t_fd		filedata;
	t_daft_node	**node;
	char		*filename;
	int			size;
	int			first_node;
	int			iterator;
	char		field_sep[2];
	char		key_value_sep[2];
	char		values_sep[2];
	t_bool		multiple_lines:1;
	t_bool		split_values:1;
	t_bool		edit:1;
	t_bool		append:1;
};

struct s_daft_node
{
	t_daft_node	*next;
	int			offset;
};

enum e_daft_logs
{
	DAFT_MESSAGES,
	DAFT_ERRORS,
	DAFT_LOG_OPEN,
	DAFT_LOG_ATOI,
	DAFT_LOG_MALLOC,
	DAFT_LOG_USAGE,
	DAFT_LOG_PARAM,
	DAFT_LOG_SETT,
	DAFT_LOG_FILESETT,
	DAFT_LOG_ALLOCSIZE,
	DAFT_LOG_MISSFLAGS,
	DAFT_LOG_NOMEM,
	DAFT_LOG_KEYUSED,
	DAFT_LOG_ENUM_ID,
	DAFT_LOG_ITER,
};

enum e_daft_mem
{
	NO_MEM,
	STRING,
	TWO_D_MATRIX,
	TWO_D_MATRIX_VERTICAL,
	THREE_D_MATRIX,
};

int			_daft_save_config(t_daft_data *data);
int			_daft_save_fnames(t_daft_data *data);
char		*_daft_get_flags(t_daft_data *data, int fnum);
int			_daft_get_data(t_daft_list *file, char *filename, int fnum);
int			_daft_get_data2(t_daft_list *file);
int			_daft_log(int log);
int			_daft_start_list(t_daft_node **list, int offset);
int			_daft_add_node_back(t_daft_node	*list, int offset);
t_daft_data	*_daft_get_memory(t_daft_data *new_data, bool update);
int			_daft_resize_matr(char ***old_matr, int *size, int min_alloc);
int			_daft_resize_three_d_matr(char ****old_matr, int *size, int min_alloc);
char		*_cat_string(char *src, char *catstr, size_t start, int which_free);
int			_daft_hash(t_daft_list *file, const char *key);
char		**_daft_split(char const *s, char c, int string_size, int matr_size);
uint32_t	murmurhash2(const void *key, int len, uint32_t seed);
char		*_daft_get_key(t_daft_data *dt, t_daft_list *f, const char *s, t_fd fd);
char		*_daft_get_hash_filename(char *filename);
int			_daft_edit_hash_file(t_daft_list *list, int f_num);
int			_daft_prep_prog(char *fnames[2], char *flags, int f_num, int f_size);

int			_daft_add_mem(t_daft_data *data);
void		_daft_free_mem(t_daft_data *data, int call_n);
t_daft_mem	*_daft_old_mem_node(t_daft_data *data, int n);

int		_daft_find_data_type(t_daft_list *file);
void	*_daft_select_mem_type(t_daft_data *data, t_daft_list *file, char *key);
int		_daft_open_files(t_daft_data *data, char *f_read, char *f_write);
int		_daft_append_files(t_daft_data *data, char *f_read, char *f_write);
void	*_daft_get_string(t_daft_data *data, t_daft_list *file, char *key);
void	*_daft_get_vertical_matr(t_daft_data *data, t_daft_list *file);
void	*_daft_get_horiz_matr(t_daft_data *data, t_daft_list *file, char *key);
void	*_daft_get_three_d_matr(t_daft_data *data, t_daft_list *file);

int			_daft_update_data(t_daft_data *data, int i);
void		_daft_append_data(t_daft_data *data, t_daft_list *file, int file_n);
void		_daft_edit_f(t_daft_data *dt, int i, char **line, t_daft_mem *mem);
void		_daft_append_f(t_daft_data *dt, int i, char **line, t_daft_mem *mem);

#endif