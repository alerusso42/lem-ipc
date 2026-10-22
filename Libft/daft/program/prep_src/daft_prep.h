/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft_prep.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:48:32 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/27 17:18:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAFT_PREP_H
# define DAFT_PREP_H
# include "../../daft.h"
# define SEED 42

typedef struct s_daft_hash
{
	int	key;
	int	pos;
}	t_daft_hash;

typedef struct s_daft_prep
{
	t_fd		data_fd;
	t_fd		hash_fd;
	char		separator[3];
	t_daft_hash	*hash_table;
	char		*flags;
	char		*data_file;
	char		*hash_file;
	int			*collision;
	int			file_num;
	int			file_size;
	int			hash_size;
	int			alloc_size;
	bool		exit;
}	t_daft_prep;

enum e__daft_prep_error
{
	ER_OK,
	ER_OPEN,
	ER_ATOI,
	ER_MALLOC,
};

//SECTION -	collision

void	_daft_coll_upd(t_daft_prep *data, int old_key, int lowest_key, int *i);
int		_daft_coll_check(t_daft_prep *data, int hash_pos);

//SECTION -	_daft_fill_hash_table

void	_daft_fill_hash_table(t_daft_prep *data);

//SECTION -	hash

int		_daft_ft_hash(t_daft_prep *data, char *key);

//SECTION -	memory

void	_daft_prep_alloc_memory(t_daft_prep *data);
void	_daft_prep_free_memory(t_daft_prep *data);
void	_daft_prep_error(t_daft_prep *data, int err_type);

//SECTION -	_daft_prep_parse_args

void	_daft_prep_parse_args(t_daft_prep *data, char *argv[]);

//SECTION -	print

void	_daft_print_filedata(t_daft_prep *data);
void	_daft_print_hash_table(t_daft_prep *data);

//SECTION -	utils

void	_daft_make_float(t_daft_prep *data, char *str, double *result);
int		_daft_num_size(int n);
int		_daft_count_char(char *str, char c);
int		_daft_ft_abs(int n);
void	_daft_find_lowest_key(t_daft_prep *data, int *lowest_key, int *struct_i);

#endif