/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_bubblesort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:09:02 by marvin            #+#    #+#             */
/*   Updated: 2023/04/24 12:09:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

#include <stdio.h>

/*
int ps_goodswap(t_pslist *list)
{
	int piv;
	int next;

	piv = list->pivot->data;
	next = list->pivot->next->data;
	if (piv > next && !(piv == list->max && next == list->min))
		return (1);
	return (0);
}

void 	ps_bubble_front(t_pslist *list, int times)
{
	while (times--)
	{
		if (ps_goodswap(list))
		{
			pslist_swap_top(list, "sa");
			ft_printf("sa\n");
		}
		pslist_rotate(list, 1, "ra");
	}
}

void 	ps_bubble_back(t_pslist *list, int times)
{
	while (times--)
	{
		if (ps_goodswap(list))
		{
			pslist_swap_top(list, "sa");
			ft_printf("sa\n");
		}
		pslist_rotate(list, 1, "ra");
	}
}

void 	ps_bubble_sort(t_pslist *list)
{
	ps_bubble_front(list, list->len * 3);
}*/
