/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_checker_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:59:51 by marvin            #+#    #+#             */
/*   Updated: 2023/05/03 09:59:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap_checker_bonus.h"

int	op_swap(t_ps_stack *a_stack, t_ps_stack *b_stack, \
char *op, t_pscount *counter)
{
	if (!ft_strncmp(op, "sa\n", 3))
	{
		pslist_swap_top(a_stack, FALSE);
		(counter->sa_count)++;
	}
	else if (!ft_strncmp(op, "sb\n", 3))
	{
		pslist_swap_top(b_stack, FALSE);
		(counter->sb_count)++;
	}
	else if (!ft_strncmp(op, "ss\n", 3))
	{
		pslist_swap_top(a_stack, FALSE);
		pslist_swap_top(b_stack, FALSE);
		(counter->ss_count)++;
	}
	else
		return (0);
	return (1);
}

int	op_reverse_rotation(t_ps_stack *a_stack, t_ps_stack *b_stack, \
char *op, t_pscount *counter)
{
	if (!ft_strncmp(op, "rra\n", 4))
	{
		pslist_rotate(a_stack, -1, FALSE);
		(counter->rra_count)++;
	}
	else if (!ft_strncmp(op, "rrb\n", 4))
	{
		pslist_rotate(b_stack, -1, FALSE);
		(counter->rrb_count)++;
	}
	else if (!ft_strncmp(op, "rrr\n", 4))
	{
		pslist_rotate(a_stack, -1, FALSE);
		pslist_rotate(b_stack, -1, FALSE);
		(counter->rrr_count)++;
	}
	else
		return (0);
	return (1);
}

int	op_rotation(t_ps_stack *a_stack, t_ps_stack *b_stack, \
char *op, t_pscount *counter)
{
	if (!ft_strncmp(op, "ra\n", 3))
	{
		pslist_rotate(a_stack, 1, FALSE);
		(counter->ra_count)++;
	}
	else if (!ft_strncmp(op, "rb\n", 3))
	{
		pslist_rotate(b_stack, 1, FALSE);
		(counter->rb_count)++;
	}
	else if (!ft_strncmp(op, "rr\n", 3))
	{
		pslist_rotate(a_stack, 1, FALSE);
		pslist_rotate(b_stack, 1, FALSE);
		(counter->rr_count)++;
	}
	else
		return (0);
	return (1);
}

int	distribute_operations(t_ps_stack *a_stack, t_ps_stack *b_stack, \
char *op, t_pscount *counter)
{
	if (!ft_strncmp(op, "ra\n", 3) || !ft_strncmp(op, "rb\n", 3) \
	|| !ft_strncmp(op, "rr\n", 3))
		op_rotation(a_stack, b_stack, op, counter);
	else if (!ft_strncmp(op, "rra\n", 4) || !ft_strncmp(op, "rrb\n", 4) \
	|| !ft_strncmp(op, "rrr\n", 4))
		op_reverse_rotation(a_stack, b_stack, op, counter);
	else if (!ft_strncmp(op, "sa\n", 3) || !ft_strncmp(op, "sb\n", 3) \
	|| !ft_strncmp(op, "ss\n", 3))
		op_swap(a_stack, b_stack, op, counter);
	else if (!ft_strncmp(op, "pa\n", 3))
	{
		pslist_push_top(a_stack, b_stack, FALSE);
		(counter->pa_count)++;
	}
	else if (!ft_strncmp(op, "pb\n", 3))
	{
		pslist_push_top(b_stack, a_stack, FALSE);
		(counter->pb_count)++;
	}
	else
		return (0);
	return (1);
}

int	get_all_operations(t_ps_stack *a_stack, t_ps_stack *b_stack, \
t_pscount *counter)
{
	char	*line;
	int		check;

	check = 1;
	line = (char *)1;
	while (line && check)
	{
		line = get_next_line(0);
		if (line)
		{
			check = distribute_operations(a_stack, b_stack, line, counter);
			free(line);
		}
	}
	return (check);
}
