/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class_garbage_collector.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso42 <alerusso42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 10:12:14 by alerusso42        #+#    #+#             */
/*   Updated: 2026/10/01 17:21:21 by alerusso42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "string_private.h"

//ANCHOR - _str_garbage_collector
/*
	!!!This function is private! It shouldn't be used!
	
	This is the garbage collection of heap string objects.

	@input:		[t_str **str]----->	pointer to string object
				[bool delete]----->	flag to indicate deletion
	@return:	none
	@variables:	[static t_list *garbage_list]--->	list of allocated strings;
	
//REVIEW
//	1)	If delete is false, a new node is created in garbage_list;
	2)	If p is NULL, all allocated strings are deleted;
	3)	If p is the head of the list,
		the head of the list is moved forward.
*/
void	_str_garbage_collector(t_str *p, bool delete)
{
	static t_list	*garbage_list;

	if (STRING_GARBAGE_COLLECTOR == false)
		return ;
	if (delete == false)
	{
		p->_garbage_coll_node = lst_new(p);
		lst_back(&garbage_list, p->_garbage_coll_node);
		return ;
	}
	if (!p)
		return (lst_clear(&garbage_list, _str_destructor));
	else if (p->_garbage_coll_node == garbage_list)
	{
		garbage_list = garbage_list->next;
	}
}
