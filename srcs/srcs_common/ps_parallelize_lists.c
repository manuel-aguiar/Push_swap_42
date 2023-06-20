/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_combo_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:22:24 by marvin            #+#    #+#             */
/*   Updated: 2023/05/10 11:22:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

t_idmnode	*idmlist_retrieve_head(t_idmlist **list)
{
	t_idmnode	*save;

	save = (*list)->head;
	if (!save->next)
	{
		(*list)->head = NULL;
		(*list)->tail = NULL;
		ft_free_set_null(list);
	}
	else
	{
		(*list)->head = save->next;
		if (!(*list)->head->next)
			(*list)->tail = (*list)->head;
		((*list)->len)--;
	}
	save->next = NULL;
	return (save);
}

void	idmlist_node_to_tail(t_idmlist *list, t_idmnode *new_node)
{
	if (!list || !new_node)
		return ;
	if (list->tail)
	{
		new_node->prev = list->tail;
		list->tail->next = new_node;
	}
	else
		list->head = new_node;
	list->tail = new_node;
	++(list->len);
}

void	idmlist_del_head_destroy(t_idmlist **list)
{
	idmlist_del_head(*list);
	if (!(*list)->len)
		ft_free_set_null(list);
}
