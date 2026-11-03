/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 12:22:05 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/03 15:41:40 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
//SECTION - includes
#include "lem-ipc.h"
#include <sys/mman.h>
#include <sys/msg.h>
#include <sys/time.h>
#include <mqueue.h>
#include <signal.h>
#include <fcntl.h>
//SECTION - defines

//SECTION - data structures

//SECTION - functions
void	setup(t_data *data);