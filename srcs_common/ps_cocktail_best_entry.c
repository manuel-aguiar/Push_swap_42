/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_stack_cocktail.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:59:47 by marvin            #+#    #+#             */
/*   Updated: 2023/05/10 09:59:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static int	correct_place(t_icpnode *node, int len, int start)
{
	t_icpnode	*cur;
	t_icpnode	*comp;
	int			count;
	int			i;
	int			j;

	comp = node;
	cur = comp;
	i = 0;
	while (i < start)
	{
		comp = comp->next;
		i++;
	}
	count = 0;
	j = 0;
	while (j++ < len)
	{
		if (cur->data < comp->data)
			count++;
		cur = cur->next;
	}
	return (ABS((i - count)));
}

static int	score_sum(t_icpnode *node, int len)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (i < len)
	{
		res += correct_place(node, len, i);
		i++;
	}
	return (res);
}

static int	closest_path(int index, int len)
{
	if (index > len / 2)
		return (len - index);
	else
		return (index);
}

int	best_cocktail_entry(t_ps_stack *stack, int len)
{
	t_icpnode	*cur;
	int			best_index;
	int			best_score;
	int			comp;
	int			i;

	best_index = 0;
	i = 0;
	cur = stack->list->pivot;
	while (i < len)
	{
		if (i == 0)
			best_score = score_sum(cur, len);
		else
		{
			comp = score_sum(cur, len) + closest_path(i, len);
			if (comp < best_score)
			{
				best_index = i;
				best_score = comp;
			}
		}
		i++;
		cur = cur->next;
	}
	return (best_index);
}
