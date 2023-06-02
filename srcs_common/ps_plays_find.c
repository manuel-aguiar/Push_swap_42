/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_plays_find.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:17:59 by marvin            #+#    #+#             */
/*   Updated: 2023/05/11 14:17:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	find_exact_target(t_ps_stack *stack, int target)
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
		if (is_target(fwd->data, target))
			return (count);
		if (is_target(back->data, target))
			return (-count);
		fwd = fwd->next;
		back = back->prev;
		count++;
	}
	return (0);
}

int	find_mid_intersection(t_ps_stack *stack, int min, int max)
{
	int			size;
	int			count;
	int			mid;
	t_icpnode	*fwd;
	t_icpnode	*back;

	mid = (max + min) / 2;
	count = 0;
	fwd = stack->list->pivot;
	back = stack->list->pivot;
	size = stack->list->len / 2 + 1;
	while (size--)
	{
		if (in_bucket(fwd->prev->data, min, mid) \
		&& in_bucket(fwd->data, mid, max))
			return (count);
		if (in_bucket(back->prev->data, min, mid) \
		&& in_bucket(back->data, mid, max))
			return (-count);
		fwd = fwd->next;
		back = back->prev;
		count++;
	}
	return (0);
}

int	find_closest_in_bucket(t_ps_stack *stack, int min, int max)
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
		if (in_bucket(fwd->data, min, max))
			return (count);
		else
			fwd = fwd->next;
		count++;
		if (in_bucket(fwd->data, min, max))
			return (count);
		if (in_bucket(back->data, min, max))
			return (-(count / 2));
		fwd = fwd->next;
		back = back->prev;
		count++;
	}
	return (0);
}

int	find_bucket_ends(t_ps_stack *stack, int min, int max)
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
		if (in_bucket(fwd->prev->data, min, max) \
		&& !in_bucket(fwd->data, min, max))
			return (count);
		if (in_bucket(back->prev->data, min, max) \
		&& !in_bucket(back->data, min, max))
			return (-count);
		fwd = fwd->next;
		back = back->prev;
		count++;
	}
	return (0);
}

int	find_bucket_begins(t_ps_stack *stack, int min, int max)
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
		if (in_bucket(fwd->data, min, max) \
		&& !in_bucket(fwd->prev->data, min, max))
			return (count);
		if (in_bucket(back->data, min, max) \
		&& !in_bucket(back->prev->data, min, max))
			return (-count);
		fwd = fwd->next;
		back = back->prev;
		count++;
	}
	return (0);
}

/*
int find_closest_in_bucket(t_ps_stack *stack, int min, int max)
{
	t_icpnode	*forward;
	t_icpnode	*backward;
	int			countpos;
	int			countneg;

	countpos = 0;
	countneg = 0;
	forward = stack->list->pivot;
	backward = stack->list->pivot;
	while (1)
	{
		if (!in_bucket(forward->data, min, max))
		{
			countpos++;
			forward = forward->next;
		}
		else
			break;
		if (!in_bucket(forward->data, min, max))
		{
			countpos++;
			forward = forward->next;
		}
		else
			break;
		if (!in_bucket(backward->data, min, max))
		{
			countneg--;
			backward = backward->prev;
		}
		else
			break;
	}

	if (in_bucket(forward->data, min, max))
		return (countpos);
	return (countneg);
}*/


/*
int find_exact_target(t_ps_stack *stack, int target)
{
	t_icpnode	*forward;
	t_icpnode	*backward;
	int			countpos;
	int			countneg;

	countpos = 0;
	countneg = 0;
	forward = stack->list->pivot;
	backward = stack->list->pivot;
	while (1)
	{
		if (!is_target(forward->data, target))
		{
			countpos++;
			forward = forward->next;
		}
		else
			break;
		if (!is_target(backward->data, target))
		{
			countneg--;
			backward = backward->prev;
		}
		else
			break;
	}
	if (is_target(forward->data, target))
		return (countpos);
	return (countneg);
}*/
