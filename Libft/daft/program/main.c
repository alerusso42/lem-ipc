/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:58:03 by alerusso          #+#    #+#             */
/*   Updated: 2025/11/27 17:20:38 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prep_src/daft_prep.h"

void	_daft_prep_error(t_daft_prep *data, int err_type);

/*
$INIT_HASH "$file" "$hash_file" $i "$delim" "${entries[$file]:0:999}"
 "$HASH_SIZE"
 chdir("../../");
*/
int	main(int argc, char *argv[])
{
	t_daft_prep	data;

	if (argc != 7)
		return (1);
	//chdir("../../");
	data = (t_daft_prep){0};
	data.exit = true;
	_daft_prep_parse_args(&data, argv);
	_daft_prep_alloc_memory(&data);
	switch_filedata(data.data_fd);
	_daft_fill_hash_table(&data);
	_daft_print_filedata(&data);
	_daft_print_hash_table(&data);
	_daft_prep_free_memory(&data);
	return (0);
}
