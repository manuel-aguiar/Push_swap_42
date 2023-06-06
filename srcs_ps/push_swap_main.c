/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:40:05 by marvin            #+#    #+#             */
/*   Updated: 2023/04/20 11:40:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	pushswap(int ac, char **av)
{
	t_ps_stack	a_stack;
	t_ps_stack	b_stack;

	if (!ps_preprocess(&(a_stack.list), ac, av) \
	|| !ps_normalize(&(a_stack.list)))
		return (error_msg());
	b_stack.list = icplist_new((a_stack.list)->len, (a_stack.list)->pool);
	if (!b_stack.list)
	{
		icplist_destroy(&(a_stack.list), 0);
		return (malloc_failed());
	}
	setup_stack_a(&a_stack);
	setup_stack_b(&b_stack);
	if (!final_sort_check(&a_stack, &b_stack, a_stack.list->len, FALSE))
		quicksort_a(&a_stack, &b_stack, 0, a_stack.list->len);
	icplist_destroy(&(b_stack.list), 1);
	icplist_destroy(&(a_stack.list), 0);
	return (1);
}

int	main(int ac, char **av)
{
	if (ac > 1)
		pushswap(--ac, ++av);
	return (0);
}

/*
$args="     "; ./push_swap $args | ./checker $args
*/
