/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_cocktail_solver.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:33:40 by marvin            #+#    #+#             */
/*   Updated: 2023/05/10 10:33:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static int	sorted_forward(t_ps_stack *stack, int min, int max, int index)
{
	t_icpnode	*cur;
	int			len;
	int			count;

	count = 0;
	cur = stack->list->pivot;
	len = max - min;
	while (in_bucket(cur->next->data, min, max) && index < len - 1)
	{
		if ((cur->data > cur->next->data && stack->ascending)\
		|| (cur->data < cur->next->data && !stack->ascending))
			return (count);
		cur = cur->next;
		index++;
		count++;
	}
	return (-1);
}

static int	sorted_backward(t_ps_stack *stack, int min, int max, int index)
{
	t_icpnode	*cur;
	int			count;

	count = -1;
	cur = stack->list->pivot;
	while (in_bucket(cur->prev->data, min, max) && index > 0)
	{
		if ((cur->data < cur->prev->data && stack->ascending)\
		|| (cur->data > cur->prev->data && !stack->ascending))
			return (count);
		cur = cur->prev;
		index--;
		count--;
	}
	return (1);
}

void	internal_cocktail(t_ps_stack *stack, int min, int max, int options)
{
	int	i;
	int	rotate;

	i = get_stack_to_best_entry(stack, min, max, options);
	while (sorted_forward(stack, min, max, i) != -1 \
		|| sorted_backward(stack, min, max, i) != 1)
	{
		rotate = sorted_forward(stack, min, max, i);
		pushswap_sort_two(stack, options);
		while (i < max - min - 1  && rotate != -1)
		{
			pslist_rotate(stack, rotate, options);
			i += rotate;
			pushswap_sort_two(stack, options);
			rotate = sorted_forward(stack, min, max, i);
		}
		rotate = sorted_backward(stack, min, max, i);
		while (i > 0 && rotate != 1)
		{
			pslist_rotate(stack, rotate, options);
			i += rotate;
			pushswap_sort_two(stack, options);
			rotate = sorted_backward(stack, min, max, i);
		}
	}
	go_to_endofbucket(stack, min, max, options);
}

void	stack_cocktail(t_ps_stack *stack, int min, int max, int options)
{
	if (max - min <= 2)
	{
		cocktail_two(stack, min, max, options);
		return ;
	}
	internal_cocktail(stack, min, max, options);
}
