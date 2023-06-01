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

int		closest_two_target(t_ps_stack *stack, int min, int max, int *is_max)
{
	int	dist_min;
	int	dist_max;

	dist_min = find_exact_target(stack, min);
	dist_max = find_exact_target(stack, max);
	//printf("min is %d at %d away, max is %d at %d away\n", min, dist_min, max, dist_max);
	if (ABS(dist_min) - ABS(dist_max) >= 0)
	{
		*is_max = 1;
		return (dist_max);
	}
	*is_max = 0;
	return (dist_min);
}


/*
void	collective_move(t_ps_stack *from, t_ps_stack *to, int min, int max)
{
	int mid;
	int send_dist;
	int	inter_dist;

	mid = (min + max) / 2;

	if (!(members_in_bucket(to, min, mid) && members_in_bucket(to, mid, max)))
		return ;
	send_dist = closest_two_target(from, min, max);
	inter_dist = find_mid_intersection(to, min, max);


	if (send_dist > 0 && inter_dist > 0)
	{
		while (send_dist && inter_dist)
		{
			super_rotate(from, to);
			super_swap(from, to, min, max);
			send_dist--;
			inter_dist--;
		}
	}
	if (send_dist < 0 && inter_dist < 0)
	{
		while (send_dist && inter_dist)
		{
			super_revrot(from, to);
			super_swap(from, to, min, max);
			send_dist++;
			inter_dist++;
		}
	}
}
*/

int	find_insertion_point(t_ps_stack *stack, int min, int max)
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
		&& is_target(fwd->prev->data, min)) \
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

void	move_to_begin(t_ps_stack *from, t_ps_stack *to, int min, int max)
{
	int	size;
	int	from_begin;
	int	to_begin;

	size = max - min;
	to_begin = find_exact_target(to, min);
	//printf("to begin %d\n", to_begin);
	if (from->list->len \
	&& in_bucket(from->list->pivot->prev->data, min - size, min))
	{
		from_begin = find_bucket_end_back(from, min - size, min);
		//printf("from begin %d\n", from_begin);
		if (from_begin < 0 && to_begin < 0)
		{
			while (from_begin && to_begin)
			{
				super_revrot(from, to);
				from_begin++;
				to_begin++;
			}
		}
		if (from_begin > 0 && to_begin > 0)
		{
			while (from_begin && to_begin)
			{
				super_rotate(from, to);
				from_begin--;
				to_begin--;
			}
		}
	}

	/*idmlist_head_print(from->save_plays, &print_command);
	printf("  <-INSIDE MINMAX commands saved in B AFTER COMBO COMMANDS TO BEGIN\n");
	idmlist_head_print(to->save_plays, &print_command);
	printf("  <-INSIDE MINMAX commands saved in A AFTER COMBO COMMANDS TO BEGIN\n");*/

	pslist_rotate(to, to_begin, O_PRINT | O_COUNT);
}

void	insertion_minmax(t_ps_stack *from, t_ps_stack *to, int min, int max)
{
	int	size;
	int	cur_min;
	int	cur_max;
	int	intersection;
	int	closest;
	int	is_max;

	cur_min = min;
	cur_max = max - 1;
	size = max - min;
	while (size--)
	{
		closest = closest_two_target(from, cur_min, cur_max, &is_max);
		if (!members_in_bucket(to, min, cur_min))
			intersection = 0;
		else if(!members_in_bucket(to, cur_max, max))
			intersection = find_bucket_ends(to, min, cur_min);
		else
			intersection = find_insertion_point(to, cur_min - 1, cur_max + 1);
		if (closest > 0 && intersection > 0)
		{
			while (closest && intersection)
			{
				super_rotate(from, to);
				closest--;
				intersection--;
			}
		}
		else  if (closest < 0 && intersection < 0)
		{
			while (closest && intersection)
			{
				super_revrot(from, to);
				closest++;
				intersection++;
			}
		}
		pslist_rotate(from, closest, O_PRINT | O_COUNT);
		pslist_rotate(to, intersection, O_PRINT | O_COUNT);
		if (from->trial_mode || to->trial_mode)
			merge_plays(from, to);
		pslist_push_top(to, from, O_PRINT | O_COUNT);
		if (is_max)
			cur_max--;
		else
			cur_min++;
	}
	move_to_begin(from, to, min, max);
}
