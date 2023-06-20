/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_quicksort_moves.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:56:46 by marvin            #+#    #+#             */
/*   Updated: 2023/05/09 16:56:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	swap_when_pushing(t_ps_stack *stack, int min, int max)
{
	t_icpnode	*cur;

	cur = stack->list->pivot;
	if (((cur->data == cur->next->data + 1 && stack->ascending) \
	|| ((cur->data == cur->next->data - 1 && !stack->ascending))) \
	&& !in_bucket(cur->data, min, max) \
	&& !in_bucket(cur->next->data, min, max))
		pslist_swap_top(stack, O_PRINT | O_COUNT);
}

void	pushbucket(t_ps_stack *from, t_ps_stack *to, int min, int max)
{
	int	size;
	int	closest;

	size = max - min;
	while (size--)
	{
		closest = find_closest_in_bucket(from, min, max);
		if (closest < 0)
		{
			while (closest++ < 0)
			{
				super_swap(from, to, min, max);
				pslist_rotate(from, -1, O_PRINT | O_COUNT);
			}
		}
		else if (closest > 0)
		{
			while (closest-- > 0)
			{
				super_swap(from, to, min, max);
				pslist_rotate(from, 1, O_PRINT | O_COUNT);
			}
		}
		pslist_push_top(to, from, O_PRINT | O_COUNT);
	}
}

void	swap_when_inserting(t_ps_stack *stack, int target, int min, int max)
{
	t_icpnode	*cur;

	if (stack->list->len <= 1)
		return ;
	cur = stack->list->pivot;
	if (((cur->data == cur->next->data + 1 && stack->ascending) \
	|| (cur->data == cur->next->data - 1 && !stack->ascending)) \
	&& !is_target(cur->data, target) \
	&& !is_target(cur->next->data, target) \
	&& in_bucket(cur->data, min, max) \
	&& in_bucket(cur->next->data, min, max))
	{
		pslist_swap_top(stack, O_PRINT | O_COUNT);
	}
}

void	insertion_sort_push(t_ps_stack *from, t_ps_stack *to, \
int start, int end)
{
	int	size;

	size = end - start;
	if (from->ascending)
	{
		while (size--)
		{
			go_to_target_swap(from, start, start, end);
			start++;
			pslist_push_top(to, from, O_PRINT | O_COUNT);
		}
	}
	else
	{
		while (size--)
		{
			--end;
			go_to_target_swap(from, end, start, end);
			pslist_push_top(to, from, O_PRINT | O_COUNT);
		}
	}
}
