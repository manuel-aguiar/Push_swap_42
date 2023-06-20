/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_combo_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:12:27 by marvin            #+#    #+#             */
/*   Updated: 2023/05/10 11:12:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static int	find_common(t_ps_stack *lead, t_ps_stack *find, int *how_far)
{
	t_idmnode	*l;
	t_idmnode	*f;
	int			equiv;

	if (!lead->save_plays || !find->save_plays)
		return (0);
	l = lead->save_plays->head;
	f = find->save_plays->head;
	(*how_far) = 0;
	equiv = num_inst_equiv(lead, find, l->data);
	while (f && f->data != equiv)
	{
		(*how_far)++;
		f = f->next;
	}
	if (!f)
	{
		(*how_far) = -1;
		return (0);
	}
	if (f->data == equiv)
		return (l->data);
	return (0);
}

static int	closest_common(t_ps_stack *a_stack, t_ps_stack *b_stack, \
int *is_from_a)
{
	int	far_in_b;
	int	far_in_a;
	int	common_a;
	int	common_b;

	common_a = find_common(a_stack, b_stack, &far_in_b);
	common_b = find_common(b_stack, a_stack, &far_in_a);
	if (!common_a && !common_b)
		return (0);
	if (!common_a || far_in_b > far_in_a)
	{
		*is_from_a = 0;
		return (common_b);
	}
	if (!common_b || far_in_b <= far_in_a)
	{
		*is_from_a = 1;
		return (common_a);
	}
	return (0);
}

static void	merge_combo(t_idmlist *combo, t_ps_stack *a_stack, \
t_ps_stack *b_stack, int target)
{
	int	equiv;

	equiv = num_inst_equiv(a_stack, b_stack, target);
	while (a_stack->save_plays && a_stack->save_plays->head->data != target)
		idmlist_node_to_tail(combo, \
		idmlist_retrieve_head(&(a_stack->save_plays)));
	equiv = num_inst_equiv(a_stack, b_stack, target);
	while (b_stack->save_plays && b_stack->save_plays->head->data != equiv)
		idmlist_node_to_tail(combo, \
		idmlist_retrieve_head(&(b_stack->save_plays)));
	idmlist_in_tail(combo, num_combo_equiv(a_stack, b_stack, target));
	idmlist_del_head_destroy(&(a_stack->save_plays));
	idmlist_del_head_destroy(&(b_stack->save_plays));
}

void	intersect_plays(t_idmlist *combo, t_ps_stack *a_stack, \
t_ps_stack *b_stack)
{
	int	target;
	int	equiv;
	int	is_from_a;

	while (a_stack->save_plays || b_stack->save_plays)
	{
		target = closest_common(a_stack, b_stack, &is_from_a);
		if (!target)
		{
			while (a_stack->save_plays)
				idmlist_node_to_tail(combo, \
				idmlist_retrieve_head(&(a_stack->save_plays)));
			while (b_stack->save_plays)
				idmlist_node_to_tail(combo, \
				idmlist_retrieve_head(&(b_stack->save_plays)));
		}
		else if (is_from_a)
			merge_combo(combo, a_stack, b_stack, target);
		else
		{
			equiv = num_inst_equiv(a_stack, b_stack, target);
			merge_combo(combo, a_stack, b_stack, equiv);
		}
	}
}

void	merge_plays(t_ps_stack *receiver, t_ps_stack *sender)
{
	if (!receiver->save_plays)
	{
		receiver->save_plays = sender->save_plays;
		sender->save_plays = NULL;
	}
	else if (!sender->save_plays)
		return ;
	else
	{
		receiver->save_plays->tail->next = sender->save_plays->head;
		sender->save_plays->head->prev = receiver->save_plays->tail;
		receiver->save_plays->tail = sender->save_plays->tail;
		receiver->save_plays->len += sender->save_plays->len;
		sender->save_plays->head = NULL;
		sender->save_plays->tail = NULL;
		idmlist_destroy(&(sender->save_plays));
	}
}
