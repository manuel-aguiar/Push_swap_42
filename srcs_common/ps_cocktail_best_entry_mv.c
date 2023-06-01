/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_cocktail_best_entry_mv.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:09:04 by marvin            #+#    #+#             */
/*   Updated: 2023/05/10 10:09:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

t_icpnode	*get_stack_to_place(t_ps_stack *stack, int current, \
int target, int options)
{
	int	len;
	int	move;

	len = stack->list->len;
	move = len - current + target;
	if (move > len / 2)
		pslist_rotate(stack, len - move, options);
	else
		pslist_rotate(stack, move, options);
	return (stack->list->pivot);
}

int	bucket_is_alone_in_list(t_ps_stack *stack, int min, int max)
{
	t_icpnode	*cur;
	int			size;
	int			i;

	size = max - min + 1;
	cur = stack->list->pivot;
	i = 0;
	while (i < size && in_bucket(cur->data, min, max))
	{
		cur = cur->next;
		i++;
	}
	if (i == size)
		return (1);
	return (0);
}

int	find_end_of_bucket(t_ps_stack *stack, int min, int max, int options)
{
	t_icpnode	*cur;
	int			i;
	int			size;
	int			closest;

	size = max - min;
	cur = stack->list->pivot;
	if (!in_bucket(cur->data, min, max))
	{
		closest = find_closest_in_bucket(stack, min, max);
		pslist_rotate(stack, closest, options);
		if (closest > 0)
			return (0);
		else
			return (size - 1);
	}
	i = 0;
	while (in_bucket(cur->next->data, min, max))
	{
		cur = cur->next;
		i++;
	}
	return (size - i - 1);
}

int	get_stack_to_best_entry(t_ps_stack *stack, int min, int max, int options)
{
	int	len;
	int	best_index;

	if (!bucket_is_alone_in_list(stack, min, max))
		return (find_end_of_bucket(stack, min, max, options));
	len = stack->list->len;
	best_index = best_cocktail_entry(stack, stack->list->len);
	if (best_index > len / 2)
		pslist_rotate(stack, len / 2 - best_index, options);
	else
		pslist_rotate(stack, best_index, options);
	return (0);
}
