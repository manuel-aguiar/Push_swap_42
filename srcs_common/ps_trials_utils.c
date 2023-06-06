/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_trials_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:37:55 by marvin            #+#    #+#             */
/*   Updated: 2023/05/11 15:37:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	trial_minmax(t_ps_stack *challenger, t_idmlist **record)
{
	t_idmnode	*cur;
	int			count;

	count = 0;
	cur = challenger->save_plays->tail;
	while (cur && (cur->data != challenger->codes.rr_num \
		&& cur->data != challenger->codes.rrr_num))
		cur = cur->prev;
	while (cur && (cur->data == challenger->codes.rr_num \
		|| cur->data == challenger->codes.rrr_num))
	{
		count++;
		cur = cur->prev;
	}
	if (challenger->save_plays->len - count < (*record)->len)
	{
		idmlist_destroy(record);
		*record = challenger->save_plays;
		challenger->save_plays = NULL;
	}
	else
		idmlist_destroy(&(challenger->save_plays));
}

void	trial_judge(t_ps_stack *challenger, t_idmlist **record, int first_try)
{
	if (first_try)
	{
		*record = challenger->save_plays;
		challenger->save_plays = NULL;
		return ;
	}
	if (challenger->save_plays->len < (*record)->len)
	{
		idmlist_destroy(record);
		*record = challenger->save_plays;
		challenger->save_plays = NULL;
	}
	else
		idmlist_destroy(&(challenger->save_plays));
}
