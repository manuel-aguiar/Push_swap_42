/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_execute_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:56:03 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/06/01 16:50:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	execute_combo(t_ps_stack *stack, t_ps_stack *other, \
int command, int options)
{
	if (command == stack->codes.ss_num)
	{
		pslist_swap_top(stack, options | O_COMBO);
		pslist_swap_top(other, options | O_COMBO);
		if (options & O_PRINT)
			ft_printf("%s", stack->swap_combo);
	}
	else if (command == stack->codes.rr_num)
	{
		pslist_rotate(stack, 1, options | O_COMBO);
		pslist_rotate(other, 1, options | O_COMBO);
		if (options & O_PRINT)
			ft_printf("%s", stack->rotate_combo);
	}
	else if (command == stack->codes.rrr_num)
	{
		pslist_rotate(stack, -1, options | O_COMBO);
		pslist_rotate(other, -1, options | O_COMBO);
		if (options & O_PRINT)
			ft_printf("%s", stack->revrot_combo);
	}
	else
		return (0);
	return (1);
}

int	execute_single(t_ps_stack *stack, t_ps_stack *other, \
int command, int options)
{
	if (command == stack->my_push_num)
		return (pslist_push_top(other, stack, options));
	if (command == stack->my_swap_num)
		return (pslist_swap_top(stack, options));
	if (command == stack->my_rot_num)
		return (pslist_rotate(stack, 1, options));
	if (command == stack->my_revrot_num)
		return (pslist_rotate(stack, -1, options));
	return (0);
}

int	execute_list_rev(t_ps_stack *a_stack, t_ps_stack *b_stack, \
t_idmlist *ops, int options)
{
	t_idmnode	*inst;
	int			reverse;

	inst = ops->tail;
	while (inst)
	{
		reverse = num_inst_reverse(a_stack, b_stack, inst->data);
		if (!execute_single(a_stack, b_stack, reverse, options) \
		&& !execute_single(b_stack, a_stack, reverse, options) \
		&& !execute_combo(a_stack, b_stack, reverse, options))
			return (0);
		inst = inst->prev;
	}
	return (1);
}

int	execute_list(t_ps_stack *a_stack, t_ps_stack *b_stack, \
t_idmlist *ops, int options)
{
	t_idmnode	*inst;

	inst = ops->head;
	while (inst)
	{
		if (!execute_single(a_stack, b_stack, inst->data, options) \
		&& !execute_single(b_stack, a_stack, inst->data, options) \
		&& !execute_combo(a_stack, b_stack, inst->data, options))
			return (0);
		inst = inst->next;
	}
	return (1);
}
