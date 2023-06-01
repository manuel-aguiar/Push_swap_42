/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_cocktail_parallel.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:19:26 by marvin            #+#    #+#             */
/*   Updated: 2023/05/10 11:19:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static void	parallel_join(t_ps_stack *lead, t_idmlist *saved, t_idmlist *combo)
{
	lead->save_plays = saved;
	if (!lead->save_plays)
		lead->save_plays = combo;
	else if (combo->head)
	{
		lead->save_plays->tail->next = combo->head;
		combo->head->prev = lead->save_plays->tail;
		lead->save_plays->tail = combo->tail;
		lead->save_plays->len += combo->len;
		combo->head = NULL;
		combo->tail = NULL;
	}
}

void	parallel_cocktail(t_ps_stack *lead, t_ps_stack *follow, \
int min, int max)
{
	t_idmlist	*combo;
	t_idmlist	*save_prev;

	int		mid;
	mid = (min + max) / 2;
	combo = idmlist_new();
	if (lead->trial_mode || follow->trial_mode)
	{
		merge_plays(lead, follow);
		save_prev = lead->save_plays;
		lead->save_plays = NULL;
	}
	stack_cocktail(lead, mid, max, O_SAVE);
	stack_cocktail(follow, min, mid, O_SAVE);
	intersect_plays(combo, lead, follow);
	if (lead->trial_mode || follow->trial_mode)
		parallel_join(lead, save_prev, combo);
	else
		idmlist_head_print(combo, &printmembs);
	idmlist_destroy(&combo);
}
