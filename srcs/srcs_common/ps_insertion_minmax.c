/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_insertion_minmax.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:47:38 by marvin            #+#    #+#             */
/*   Updated: 2023/05/12 14:47:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static int	find_insertion_point(t_ps_stack *stack, int min, int max)
{
	int			size;
	int			count;
	t_icpnode	*fwd;
	t_icpnode	*back;

	count = 0;
	fwd = stack->list->pivot;
	back = stack->list->pivot;
	size = stack->list->len / 2 + 1;
	while (size--)
	{
		if (is_target(fwd->data, max) \
		&& is_target(fwd->prev->data, min))
			return (count);
		if (is_target(back->data, max) \
		&& is_target(back->prev->data, min))
			return (-count);
		fwd = fwd->next;
		back = back->prev;
		count++;
	}
	return (0);
}

static void	collective_move(t_ps_stack *from, t_ps_stack *to, \
int *from_begin, int *to_begin)
{
	if (*from_begin < 0 && *to_begin < 0)
	{
		while (*from_begin && *to_begin)
		{
			super_revrot(from, to);
			(*from_begin)++;
			(*to_begin)++;
		}
	}
	if (*from_begin > 0 && *to_begin > 0)
	{
		while (*from_begin && *to_begin)
		{
			super_rotate(from, to);
			(*from_begin)--;
			(*to_begin)--;
		}
	}
}

static void	move_to_begin(t_ps_stack *from, t_ps_stack *to, int min, int max)
{
	int	size;
	int	from_begin;
	int	to_begin;

	size = max - min;
	to_begin = find_exact_target(to, min);
	if (from->list->len \
	&& in_bucket(from->list->pivot->prev->data, min - size, min))
	{
		from_begin = find_bucket_end_back(from, min - size, min);
		collective_move(from, to, &from_begin, &to_begin);
	}
	pslist_rotate(to, to_begin, O_PRINT | O_COUNT);
}

static void	insertion_minmax_help(t_ps_stack *from, t_ps_stack *to, \
int *closest, int *intersection)
{
	collective_move(from, to, closest, intersection);
	pslist_rotate(from, *closest, O_PRINT | O_COUNT);
	pslist_rotate(to, *intersection, O_PRINT | O_COUNT);
	if (from->trial_mode || to->trial_mode)
		merge_plays(from, to);
	pslist_push_top(to, from, O_PRINT | O_COUNT);
}

void	insertion_minmax(t_ps_stack *from, t_ps_stack *to, int min, int max)
{
	int	cur_min;
	int	cur_max;
	int	intersection;
	int	closest;
	int	is_max;

	cur_min = min;
	cur_max = max - 1;
	while (cur_max - cur_min + 1)
	{
		closest = closest_two_target(from, cur_min, cur_max, &is_max);
		if (!members_in_bucket(to, min, cur_min))
			intersection = 0;
		else if (!members_in_bucket(to, cur_max, max))
			intersection = find_bucket_ends(to, min, cur_min);
		else
			intersection = find_insertion_point(to, cur_min - 1, cur_max + 1);
		insertion_minmax_help(from, to, &closest, &intersection);
		if (is_max)
			cur_max--;
		else
			cur_min++;
	}
	move_to_begin(from, to, min, max);
}
