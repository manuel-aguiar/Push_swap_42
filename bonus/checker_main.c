/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:22:19 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/06/06 18:22:19 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap_checker.h"

void	ok_reaction(t_pscount *counter)
{
	ok_message();
	print_counter(counter);
}

void	ko_reaction(t_ps_stack *a_stack, t_ps_stack *b_stack, \
t_pscount *counter)
{
	ko_message();
	ps_printlists(a_stack->list, b_stack->list, &printmembs);
	print_counter(counter);
}

void	stack_and_counter(t_ps_stack *a_stack, t_ps_stack *b_stack, \
t_pscount *counter, int *total_len)
{
	*total_len = a_stack->list->len;
	setup_stack_a(a_stack);
	setup_stack_b(b_stack);
	set_counter_on_stack(counter, *total_len);
}

int	checker_solver(int ac, char **av)
{
	t_ps_stack	a_stack;
	t_ps_stack	b_stack;
	t_pscount	counter;
	int			total_len;

	if (!ps_preprocess(&(a_stack.list), ac, av) \
	|| !ps_normalize(&(a_stack.list)))
		return (error_msg());
	b_stack.list = icplist_new((a_stack.list)->len, (a_stack.list)->pool);
	if (!b_stack.list)
	{
		icplist_destroy(&(a_stack.list), 0);
		return (malloc_failed());
	}
	stack_and_counter(&a_stack, &b_stack, &counter, &total_len);
	if (!get_all_operations(&a_stack, &b_stack, &counter))
		error_msg();
	else if (final_sort_check(&a_stack, &b_stack, total_len, FALSE))
		ok_reaction(&counter);
	else
		ko_reaction(&a_stack, &b_stack, &counter);
	icplist_destroy(&(b_stack.list), 1);
	icplist_destroy(&(a_stack.list), 0);
	return (1);
}

int	main(int ac, char **av)
{
	if (ac > 1)
		checker_solver(--ac, ++av);
	return (0);
}
