/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_sorting_pushswap.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:11:41 by marvin            #+#    #+#             */
/*   Updated: 2023/04/27 15:11:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	last_sorted_number(t_ps_stack *stack, int start, int end)
{
	int			move_to_tgt;
	t_icpnode	*cur;

	if (end - start == stack->list->len)
		return (end);
	move_to_tgt = find_exact_target(stack, end - 1);
	cur = stack->list->pivot;
	if (move_to_tgt > 0)
	{
		while (move_to_tgt--)
			cur = cur->next;
	}
	if (move_to_tgt < 0)
	{
		while (move_to_tgt++)
			cur = cur->prev;
	}
	if (end - start < stack->list->len && cur->next->data != end)
		return (end);
	while (cur->prev->data == cur->data - 1)
	{
		end--;
		cur = cur->prev;
	}
	return (end - 1);
}


void	quicksort_b(t_ps_stack *a_stack, t_ps_stack *b_stack, int start, int end)
{
	int mid;
	int	quarter;

	//printf("quicksort B start %d, end %d\n", start, end);
	//ps_printlists(a_stack->list, b_stack->list, &printmembs);
	if (bucket_is_sorted(b_stack, start, end))
	{
		insertion_sort_push(b_stack, a_stack, start, end);
		return ;
	}
	if (end - start < INSORT_TO_A)
	{
		b_stack_trials(a_stack, b_stack, start, end);
		//insertion_sort_push(b_stack, a_stack, start, end);
		return ;
	}

	mid = (start + end) / 2;
	if (mid - start > PUSHBUCKET_LIM)
	{
		pushbucket_divide_col(b_stack, a_stack, mid, end);
		quarter = (mid + end) / 2;
		quicksort_a(a_stack, b_stack, quarter, end);
		quicksort_a(a_stack, b_stack, mid, quarter);
		quicksort_b(a_stack, b_stack, start, mid);
	}
	else
	{
		pushbucket(b_stack, a_stack, mid, end);
		quicksort_a(a_stack, b_stack, mid, end);
		quicksort_b(a_stack, b_stack, start, mid);
	}
}

/*	pushbucket(b_stack, a_stack, mid, end);
	quicksort_a(a_stack, b_stack, mid, end);
	quicksort_b(a_stack, b_stack, start, mid);*/

/*
	mid = (start + end) / 2;
	pushbucket_divide_col(b_stack, a_stack, mid, end);
	quarter = (mid + end) / 2;
	quicksort_a(a_stack, b_stack, quarter, end);
	quicksort_a(a_stack, b_stack, mid, quarter);
	quicksort_b(a_stack, b_stack, start, mid);*/

void quicksort_a(t_ps_stack *a_stack, t_ps_stack *b_stack, \
int start, int end)
{
	int mid;
	int quarter;

	//printf("quicksort A start %d, end %d\n", start, end);
	if (bucket_is_sorted(a_stack, start, end))
		return ;
	end = last_sorted_number(a_stack, start, end);


	if (end - start < INSORT_TO_B)
	{

		//insertion_sort_push(a_stack, b_stack, start, end);
		//insertion_sort_push(b_stack, a_stack, start, end);

		a_stack_trials(a_stack, b_stack, start, end);

		return ;
	}
	mid = (start + end) / 2;
	if (mid - start > PUSHBUCKET_LIM)
	{
		//printf("pushbucket A start %d, end %d\n", start, mid);
		pushbucket_divide_col(a_stack, b_stack, start, mid);
		//printf("qs from A to A, mid %d, end %d\n", mid, end);
		quicksort_a(a_stack, b_stack, mid, end);
		quarter = (start + mid) / 2;
		//printf("qs from A to B - first, quarter %d, mid %d\n", quarter, mid);
		quicksort_b(a_stack, b_stack, quarter, mid);
		//printf("qs from A to B - second, start %d, quarter %d\n", start, quarter);
		quicksort_b(a_stack, b_stack, start, quarter);
	}
	else
	{
		pushbucket(a_stack, b_stack, start, mid);
		quicksort_a(a_stack, b_stack, mid, end);
		quicksort_b(a_stack, b_stack, start, mid);
	}
}
/*
	pushbucket(b_stack, a_stack, mid, end);
	quicksort_a(a_stack, b_stack, mid, end);
	quicksort_b(a_stack, b_stack, start, mid);
*/

/*
//printf("pushbucket A start %d, end %d\n", start, mid);
	pushbucket_divide_col(a_stack, b_stack, start, mid);
	//printf("qs from A to A, mid %d, end %d\n", mid, end);
	quicksort_a(a_stack, b_stack, mid, end);
	quarter = (start + mid) / 2;
	//printf("qs from A to B - first, quarter %d, mid %d\n", quarter, mid);
	quicksort_b(a_stack, b_stack, quarter, mid);
	//printf("qs from A to B - second, start %d, quarter %d\n", start, quarter);
	quicksort_b(a_stack, b_stack, start, quarter);
*/
