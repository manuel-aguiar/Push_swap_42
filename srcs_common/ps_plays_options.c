/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_plays_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:36:29 by marvin            #+#    #+#             */
/*   Updated: 2023/05/10 09:36:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	save_command(t_ps_stack *stack, int command)
{
	if (!stack->save_plays)
		stack->save_plays = idmlist_new();
	if (!stack->save_plays)
		return (0);
	if (idmlist_in_tail(stack->save_plays, command))
		return (1);
	return (0);
}

void	ps_manage_options(t_ps_stack *stack, int options, \
char *cmd, int cmd_num)
{
	if (options & O_PRINT && !stack->trial_mode && !(options & O_COMBO))
		ft_printf("%s", cmd);
	if (options & O_COUNT && !stack->trial_mode && !(options & O_COMBO))
		(stack->op_counter)++;
	if (!(options & O_COMBO) && (options & O_SAVE \
		|| (stack->trial_mode && (!(options & O_REVERSE)))))
		save_command(stack, cmd_num);
}
