/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daft.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:27:31 by alerusso          #+#    #+#             */
/*   Updated: 2026/10/02 13:50:24 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAFT_H
# define DAFT_H

# include "../libft.h"
# include "../files/mfile.h"

/*WARNING: 	don't modify this file directly!
			modify SETTINGS.md instead!
*/

//SECTION - functions prototypes

int 	daft_init(const char *path, const char *settings_filename);
void	daft_quit(void);
void	daft_swap(int enum_id);
void	daft_free(void *mem);
void	*daft_get(const char *search);
bool	daft_iter(void **ptr);
int		daft_load(void);
void	*daft_edit(const char *search, int size, int mtr_number);
void	*daft_append(const char *key, int size, int mtr_number);

//SECTION - enum

typedef enum e_daft_db
{
	ENEMIES,
	MEDIA_LIST,
	POKEDEX,
}	t_daft_db;

#endif
