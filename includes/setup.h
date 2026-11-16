/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 12:22:05 by alerusso          #+#    #+#             */
/*   Updated: 2026/11/16 17:43:52 by alerusso42       ###   ########.fr       */
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
void	setup(t_proc *data);