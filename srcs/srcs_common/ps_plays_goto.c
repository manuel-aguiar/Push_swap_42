/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_plays_goto.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:18:20 by marvin            #+#    #+#             */
/*   Updated: 2023/05/11 14:18:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	go_to_target_swap(t_ps_stack *stack, int target, int min, int max)
{
	int	i;

	i = find_exact_target(stack, target);
	if (i > 0)
	{
		while (i--)
		{
			pslist_rotate(stack, 1, O_PRINT | O_COUNT);
			swap_when_inserting(stack, target, min, max);
		}
	}
	else
	{
		while (i++)
		{
			pslist_rotate(stack, -1, O_PRINT | O_COUNT);
			swap_when_inserting(stack, target, min, max);
		}
	}
}

void	go_to_intersection(t_ps_stack *stack, int min, int max, int options)
{
	int	mid;
	int	memblow;
	int	membhigh;

	mid = (max + min) / 2;
	memblow = members_in_bucket(stack, min, mid);
	membhigh = members_in_bucket(stack, mid, max);
	if (!memblow && !membhigh)
		return ;
	else if (!memblow)
		go_to_bucket_begins(stack, mid, max, options);
	else
		go_to_bucket_ends(stack, min, mid, options);
}

void	go_to_bucket_ends(t_ps_stack *stack, int min, int max, int options)
{
	pslist_rotate(stack, find_bucket_ends(stack, min, max), options);
}

void	go_to_endofbucket(t_ps_stack *stack, int min, int max, int options)
{
	if (stack->ascending)
		pslist_rotate(stack, find_exact_target(stack, min), options);
	else
		pslist_rotate(stack, find_exact_target(stack, max - 1), options);
}

void	go_to_bucket_begins(t_ps_stack *stack, int min, int max, int options)
{
	pslist_rotate(stack, find_bucket_begins(stack, min, max), options);
}
