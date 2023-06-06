/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_check_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:39:43 by marvin            #+#    #+#             */
/*   Updated: 2023/06/06 18:23:46 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	bucket_is_sorted(t_ps_stack *stack, int min, int max)
{
	t_icpnode	*cur;

	if (stack->list->len == 1)
		return (1);
	cur = stack->list->pivot;
	if (stack->ascending)
	{
		while (cur->data == min && min < max)
		{
			cur = cur->next;
			min++;
		}
	}
	else
	{
		while (cur->data == (max - 1) && min < max)
		{
			cur = cur->next;
			max--;
		}
	}
	if (min == max)
		return (1);
	return (0);
}

int	final_sort_check(t_ps_stack *a_stack, t_ps_stack *b_stack, \
int total, int print)
{
	t_icpnode	*cur;

	cur = a_stack->list->pivot;
	if (!cur || cur->data != 0 || a_stack->list->len != total)
		return (0);
	cur = cur->next;
	while (cur != a_stack->list->pivot)
	{
		if ((cur->data != cur->prev->data + 1))
		{
			if (print)
				ft_printf("FAILED AT NUMBER %d\n", cur->prev->data);
			return (0);
		}
		cur = cur->next;
	}
	if (b_stack->list->len)
		return (0);
	return (1);
}
