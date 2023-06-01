/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_plays_superswap.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:05:42 by marvin            #+#    #+#             */
/*   Updated: 2023/05/10 15:05:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	super_revrot(t_ps_stack *a_stack, t_ps_stack *b_stack)
{
	pslist_rotate(a_stack, -1, O_COMBO);
	pslist_rotate(b_stack, -1, O_COMBO);
	if (a_stack->trial_mode || b_stack->trial_mode)
		save_command(a_stack, a_stack->codes.rrr_num);
	else
		ft_printf("%s", a_stack->revrot_combo);
}

void	super_rotate(t_ps_stack *a_stack, t_ps_stack *b_stack)
{
	pslist_rotate(a_stack, 1, O_COMBO);
	pslist_rotate(b_stack, 1, O_COMBO);
	if (a_stack->trial_mode || b_stack->trial_mode)
		save_command(a_stack, a_stack->codes.rr_num);
	else
		ft_printf("%s", a_stack->rotate_combo);
}

void	super_swap(t_ps_stack *a_stack, t_ps_stack *b_stack, \
int min, int max)
{
	t_icpnode	*a_cur;
	t_icpnode	*b_cur;

	a_cur = a_stack->list->pivot;
	b_cur = b_stack->list->pivot;
	if (a_stack->list->len <= 1 || b_stack->list->len <= 1)
		return ;
	if (!in_bucket(a_cur->data, min, max) \
	|| !in_bucket(b_cur->data, min, max) \
	|| !in_bucket(a_cur->next->data, min, max) \
	|| !in_bucket(b_cur->next->data, min, max))
		return ;
	if (((a_cur->data == a_cur->next->data + 1 && a_stack->ascending) \
	|| (a_cur->data == a_cur->next->data - 1 && !a_stack->ascending)) \
	&& ((b_cur->data == b_cur->next->data + 1 && b_stack->ascending) \
	|| (b_cur->data == b_cur->next->data - 1 && !b_stack->ascending)))
	{
		pslist_swap_top(a_stack, O_COMBO);
		pslist_swap_top(b_stack, O_COMBO);
		if (a_stack->trial_mode || b_stack->trial_mode)
			save_command(a_stack, a_stack->codes.ss_num);
		else
			ft_printf("%s", a_stack->swap_combo);
	}
}
