/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_daft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:21:47 by codespace         #+#    #+#             */
/*   Updated: 2026/10/01 17:10:19 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// clear;cc -Wall -Wextra -Werror -g ./test_daft.c ./daft/program/daft_src/*.c ./daft/program/prep_src/*.c   data/list/*.c mem/*.c string/*.c printf/*.c files/*.c

void	print_3d(char ***);

int	main()
{
	char	***data;

	daft_init("daft/DATA_DIR", "SETTINGS.md");
	daft_init(NULL, NULL);
    daft_swap(POKEDEX);
	data = daft_get("CALYREX");
	if (!data)
		return (daft_quit(), 1);
	print_3d(data);
	data = daft_append("IR_GABIBBO", 0, 0);
	print_3d(data);
	for (int i = 0; i; i--)
	{
		daft_init("daft/DATA_DIR", "SETTINGS.md");
		daft_init("daft/DATA_DIR", "SETTINGS.md");
		daft_init("daft/DATA_DIR", "SETTINGS.md");
		daft_quit();
		daft_quit();
		daft_init("daft/DATA_DIR", "SETTINGS.md");
	}
	daft_quit();
	daft_init("daft/DATA_DIR", "SETTINGS.md");
	daft_swap(POKEDEX);
	while (daft_iter((void **)&data))
		print_3d(data);
	daft_quit();
}

void	print_3d(char ***s)
{
	if (!s)
		return ;
	for (int i = 0; s[i]; i++)
	{
		ft_printf("$G%s$Z: ", s[i][0]);
		for (int j = 1; s[i][j]; j++)
			ft_printf("%s\n", s[i][j]);
	}
}
