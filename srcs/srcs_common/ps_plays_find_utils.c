/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_plays_find_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:56:26 by marvin            #+#    #+#             */
/*   Updated: 2023/06/02 13:56:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	in_bucket(int target, int min, int max)
{
	if (min == max)
		return (target == min);
	return ((target >= min && target < max));
}

int	is_target(int target, int test)
{
	return (target == test);
}

int	members_in_bucket(t_ps_stack *stack, int min, int max)
{
	int			size;
	t_icpnode	*cur;

	cur = stack->list->pivot;
	size = stack->list->len;
	while (size--)
	{
		if (in_bucket(cur->data, min, max))
			return (1);
		cur = cur->next;
	}
	return (0);
}

int	full_list_is_bucket(t_ps_stack *stack, int min, int max)
{
	int			size;
	t_icpnode	*fwd;
	t_icpnode	*back;

	fwd = stack->list->pivot;
	back = stack->list->pivot;
	size = stack->list->len / 2 + 1;
	while (size--)
	{
		if (!in_bucket(fwd->data, min, max))
			return (0);
		if (!in_bucket(back->data, min, max))
			return (0);
		fwd = fwd->next;
		back = back->prev;
	}
	return (1);
}

int	last_sorted_number(t_ps_stack *stack, int start, int end)
{
	int			move_to_tgt;
	t_icpnode	*cur;

	if (end - start == stack->list->len)
		return (end);
	move_to_tgt = find_exact_target(stack, end - 1);
	cur = stack->list->pivot;
	if (move_to_tgt > 0)
	{
		while (move_to_tgt--)
			cur = cur->next;
	}
	if (move_to_tgt < 0)
	{
		while (move_to_tgt++)
			cur = cur->prev;
	}
	if (end - start < stack->list->len && cur->next->data != end)
		return (end);
	while (cur->prev->data == cur->data - 1)
	{
		end--;
		cur = cur->prev;
	}
	return (end - 1);
}
