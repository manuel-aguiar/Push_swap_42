/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_plays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:29:49 by marvin            #+#    #+#             */
/*   Updated: 2023/05/10 09:29:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	pslist_swap_top(t_ps_stack *stack, int options)
{
	t_icplist	*list;
	t_icpnode	*old_top;
	t_icpnode	*new_top;

	list = stack->list;
	if (!list || list->len <= 1)
		return (0);
	list->pivot = list->pivot->next;
	if (stack->list->len > 1)
	{
		old_top = list->pivot->prev;
		new_top = list->pivot;
		old_top->next = new_top->next;
		new_top->next->prev = old_top;
		new_top->prev = old_top->prev;
		old_top->prev->next = new_top;
		old_top->prev = new_top;
		new_top->next = old_top;
	}
	ps_manage_options(stack, options, stack->swap_name, \
	stack->my_swap_num);
	return (1);
}

static t_icpnode	*pslist_retrieve_top(t_ps_stack *stack)
{
	t_icplist	*list;
	t_icpnode	*ret;

	list = stack->list;
	if (!list || !(list->pivot))
		return (NULL);
	ret = list->pivot;
	if (list->len > 1)
	{
		list->pivot = list->pivot->next;
		ret->prev->next = ret->next;
		ret->next->prev = ret->prev;
	}
	else
		list->pivot = NULL;
	--(list->len);
	return (ret);
}

static int	pslist_add_top(t_ps_stack *stack, t_icpnode *newtop)
{
	t_icplist	*list;

	list = stack->list;
	if (!list || !newtop)
		return (0);
	if (!(list->pivot))
	{
		newtop->next = newtop;
		newtop->prev = newtop;
	}
	else
	{
		newtop->next = list->pivot;
		newtop->prev = list->pivot->prev;
		newtop->prev->next = newtop;
		newtop->next->prev = newtop;
	}
	list->pivot = newtop;
	++(list->len);
	return (1);
}


int	pslist_push_top(t_ps_stack *to, t_ps_stack *from, int options)
{
	t_icpnode	*move;

	if (!to->list || !from->list || !from->list->pivot)
		return (0);
	move = pslist_retrieve_top(from);
	if (move)
		pslist_add_top(to, move);
	ps_manage_options(from, options, from->push_name, \
	from->my_push_num);
	return (1);
}

int	pslist_rotate(t_ps_stack *stack, int rotate, int options)
{
	t_icplist	*list;

	if (rotate == 0)
		return (1);
	list = stack->list;
	if (rotate > 0)
	{
		list->pivot = list->pivot->next;
		ps_manage_options(stack, options, stack->rotate_name, \
		stack->my_rot_num);
		rotate--;
	}
	else if (rotate < 0)
	{
		list->pivot = list->pivot->prev;
		ps_manage_options(stack, options, stack->revrot_name, \
		stack->my_revrot_num);
		rotate++;
	}
	return (pslist_rotate(stack, rotate, options));
}
