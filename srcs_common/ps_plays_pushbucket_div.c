/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_plays_pushbucket_div.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:16:21 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/06/02 16:26:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static void	up_or_down(t_ps_stack *from, t_ps_stack *to, int min, int max)
{
	int	mid;
	int	data_from;
	int	data_to;

	if (!to->list->len)
	{
		pslist_push_top(to, from, O_PRINT | O_COUNT);
		return ;
	}
	mid = (max + min) / 2;
	data_from = from->list->pivot->data;
	data_to = to->list->pivot->data;
	if (to->list->len <= 1 \
	|| (in_bucket(data_from, min, mid) && full_list_is_bucket(to, mid, max)) \
	|| (in_bucket(data_from, mid, max) && full_list_is_bucket(to, min, mid)))
	{
		pslist_push_top(to, from, O_PRINT | O_COUNT);
		return ;
	}
	if (!(((data_from >= min && data_from < mid) \
	&& ( data_to >= min && data_to < mid)) \
	|| ((data_from >= mid && data_from < max) \
	&& ( data_to >= mid && data_to < max))))
		go_to_intersection(to, min, max, O_PRINT | O_COUNT);
	pslist_push_top(to, from, O_PRINT | O_COUNT);
}

static void	collective_move_help(t_ps_stack *from, t_ps_stack *to, \
int min, int max)
{
	int	send_dist;
	int	inter_dist;

	send_dist = find_closest_in_bucket(from, min, max);
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

static void	collective_move(t_ps_stack *from, t_ps_stack *to, \
int min, int max)
{
	int	mid;

	mid = (min + max) / 2;
	if (!(members_in_bucket(to, min, mid) && members_in_bucket(to, mid, max)))
		return ;
	collective_move_help(from, to, min, max);
}

void	pushbucket_divide_col(t_ps_stack *from, t_ps_stack *to, \
int min, int max)
{
	int	size;
	int	closest;

	size = max - min;
	while (size--)
	{
		collective_move(from, to, min, max);
		closest = find_closest_in_bucket(from, min, max);
		while (closest)
		{
			super_swap(from, to, min, max);
			if (closest < 0)
			{
				pslist_rotate(from, -1, O_PRINT | O_COUNT);
				closest++;
			}
			else if (closest > 0)
			{
				pslist_rotate(from, 1, O_PRINT | O_COUNT);
				closest--;
			}
		}
		up_or_down(from, to, min, max);
	}
	go_to_intersection(to, min, max, O_PRINT | O_COUNT);
}
