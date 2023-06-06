/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_cocktail_parallel_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:22:45 by marvin            #+#    #+#             */
/*   Updated: 2023/05/11 14:22:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	pushswap_sort_two(t_ps_stack *stack, int options)
{
	t_icpnode	*cur;

	cur = stack->list->pivot;
	if ((cur->data > cur->next->data && stack->ascending) \
	|| (cur->data < cur->next->data && !stack->ascending))
		pslist_swap_top(stack, options);
}

static void	pushswap_three_desc(t_ps_stack *stack, int options)
{
	t_icpnode	*cur;

	cur = stack->list->pivot;
	if (cur->data > cur->next->data && cur->data > cur->prev->data)
	{
		if (cur->next->data > cur->prev->data)
			return ;
		pslist_rotate(stack, -1, options);
		pslist_swap_top(stack, options);
	}
	else if (cur->data < cur->next->data && cur->data > cur->prev->data)
		pslist_swap_top(stack, options);
	else if (cur->data > cur->next->data && cur->data < cur->prev->data)
		pslist_rotate(stack, -1, options);
	else if (cur->data < cur->next->data && cur->data < cur->prev->data)
	{
		pslist_rotate(stack, 1, options);
		if (cur->next->data < cur->prev->data)
			pslist_swap_top(stack, options);
	}
}

static void	pushswap_three_asc(t_ps_stack *stack, int options)
{
	t_icpnode	*cur;

	cur = stack->list->pivot;
	if (cur->data < cur->next->data && cur->data < cur->prev->data)
	{
		if (cur->next->data < cur->prev->data)
			return ;
		pslist_rotate(stack, -1, options);
		pslist_swap_top(stack, options);
	}
	else if (cur->data > cur->next->data && cur->data < cur->prev->data)
		pslist_swap_top(stack, options);
	else if (cur->data < cur->next->data && cur->data > cur->prev->data)
		pslist_rotate(stack, -1, options);
	else if (cur->data > cur->next->data && cur->data > cur->prev->data)
	{
		pslist_rotate(stack, 1, options);
		if (cur->next->data > cur->prev->data)
			pslist_swap_top(stack, options);
	}
}

void	pushswap_sort_three(t_ps_stack *stack, int options)
{
	if (stack->ascending)
		pushswap_three_asc(stack, options);
	else
		pushswap_three_desc(stack, options);
}

void	cocktail_two(t_ps_stack *stack, int min, int max, int options)
{
	go_to_bucket_begins(stack, min, max, options);
	pushswap_sort_two(stack, options);
}
