/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_a_stack_trials.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:07:27 by marvin            #+#    #+#             */
/*   Updated: 2023/05/10 11:07:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	a_stack_double_ins(t_ps_stack *a_stack, t_ps_stack *b_stack, \
int min, int max)
{
	insertion_sort_push(a_stack, b_stack, min, max);
	insertion_sort_push(b_stack, a_stack, min, max);
	merge_plays(a_stack, b_stack);
	execute_list_rev(a_stack, b_stack, a_stack->save_plays, O_REVERSE);
}

void	a_stack_double_cocktail(t_ps_stack *a_stack, t_ps_stack *b_stack, \
int min, int max)
{
	int	mid;

	mid = (min + max) / 2;
	pushbucket(a_stack, b_stack, min, mid);
	parallel_cocktail(a_stack, b_stack, min, max);
	insertion_sort_push(b_stack, a_stack, min, mid);
	merge_plays(a_stack, b_stack);
	execute_list_rev(a_stack, b_stack, a_stack->save_plays, O_REVERSE);
}

void	a_stack_trials(t_ps_stack *a_stack, t_ps_stack *b_stack, \
int min, int max)
{
	t_idmlist	*best_play;

	a_stack->trial_mode = 1;
	b_stack->trial_mode = 1;
	stack_cocktail(a_stack, min, max, O_SAVE);
	trial_judge(a_stack, &best_play, TRUE);
	execute_list_rev(a_stack, b_stack, best_play, O_REVERSE);
	if (max - min > 2)
	{
		a_stack_double_cocktail(a_stack, b_stack, min, max);
		trial_judge(a_stack, &best_play, FALSE);
		a_stack_double_ins(a_stack, b_stack, min, max);
		trial_judge(a_stack, &best_play, FALSE);
	}
	a_stack->trial_mode = 0;
	b_stack->trial_mode = 0;
	execute_list(a_stack, b_stack, best_play, O_PRINT);
	idmlist_destroy(&best_play);
}
