/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_plays_find_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:18:39 by marvin            #+#    #+#             */
/*   Updated: 2023/06/02 16:18:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	closest_two_target(t_ps_stack *stack, int min, int max, int *is_max)
{
	int	dist_min;
	int	dist_max;

	dist_min = find_exact_target(stack, min);
	dist_max = find_exact_target(stack, max);
	if (ABS(dist_min) - ABS(dist_max) >= 0)
	{
		*is_max = 1;
		return (dist_max);
	}
	*is_max = 0;
	return (dist_min);
}

int	find_bucket_end_back(t_ps_stack *stack, int min, int max)
{
	int			size;
	int			count;
	t_icpnode	*back;

	count = 0;
	back = stack->list->pivot;
	size = stack->list->len;
	while (size--)
	{
		if (!in_bucket(back->prev->data, min, max))
			return (-count);
		back = back->prev;
		count++;
	}
	return (1);
}

