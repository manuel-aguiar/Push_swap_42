/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_mergeswap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:13:22 by marvin            #+#    #+#             */
/*   Updated: 2023/04/24 13:13:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"


static int counter;

int	first_order(t_pslist *list)
{
	int piv;
	int next;

	piv = list->pivot->data;
	next = list->pivot->next->data;

	if (piv > next && !(piv == list->max && next == list->min))
		return (1);
	return (0);
}

int	second_order(t_pslist *list)
{
	int piv;
	int next;

	piv = list->pivot->data;
	next = list->pivot->next->next->data;

	if (piv > next && !(piv == list->max && next == list->min))
		return (1);
	return (0);
}


void dumpable (t_pslist *alist, t_pslist *blist)
{
	int len;

	len = blist->len;
	while (blist->len)
	{
		pslist_push_top(alist, blist, "pa");
		counter++;
	}
}




void ps_split_list(t_pslist *alist, t_pslist *blist, int ac)
{
	int len;
	int i;
	int save;
	int totalplaced;
	int prev_max;
	int prev_min;

	prev_max = -1;
	prev_min = -1;
	totalplaced = 0;
	len = 1;
	save = ac;
	while (len < ac)
	{
			len *= 2;
			while (blist->len < len)
			{
				if (first_order(alist) && second_order(alist))
				{
					if (blist->len <= 1)
					{
						pslist_push_top(blist, alist, "pb");
						//ps_printlists(alist, blist, &printmembs);
					}
					else if (blist->len == 2)
					{
						if (blist->pivot->data < blist->pivot->next->data)
						{
							pslist_swap_top(alist, NULL);
							pslist_swap_top(blist, "ss");
							//ps_printlists(alist, blist, &printmembs);
							counter++;
							ps_printlists(alist, blist, &printmembs);
						}
						else
						{
							pslist_push_top(blist, alist, "pb");
							if (blist->pivot->data > blist->min && blist->pivot->data < blist->max)
								pslist_swap_top(blist, "sb");
							counter++;
							//ps_printlists(alist, blist, &printmembs);
						}
					}
					else if (blist->len > 2)
					{
						//ps_printlists(alist, blist, &printmembs);
						//printf("finding a place for %d, max is %d, min is %d\n", alist->pivot->data, blist->max, blist->min);
						find_b_place(blist, alist->pivot->data);
						pslist_push_top(blist, alist, "pb");
						counter++;
						//ps_printlists(alist, blist, &printmembs);
					}
				}
				else if (alist->pivot->data > alist->pivot->next->data && alist->pivot->data < alist->pivot->next->next->data)
				{
					if (blist->len >= 2)
					{
						if (blist->pivot->data < blist->pivot->next->data  && !(blist->pivot->data == blist->min && blist->pivot->next->data == blist->max))
						{
							pslist_swap_top(alist, NULL);
							pslist_swap_top(blist, "ss");
							counter++;
							//ps_printlists(alist, blist, &printmembs);
						}
						else
						{
							pslist_swap_top(alist, "sa");
							counter++;
							//ps_printlists(alist, blist, &printmembs);
						}
					}
					else
					{
						pslist_swap_top(alist, "sa");
						counter++;
					}
				}
				else
				{
					pslist_rotate(alist, 1, "ra");
					counter++;
					//ps_printlists(alist, blist, &printmembs);
				}
			}
			ps_printlists(alist, blist, &printmembs);
			ac -= blist->len;
			find_b_place(blist, blist->max);
			ps_printlists(alist, blist, &printmembs);
			if (prev_max != -1)
			{
				
				if (is_ordered(alist))
				{
					ft_printf("alist ios ordered\n");
					while (alist->pivot->data != alist->min)
						pslist_rotate(alist, 1, "ra");
				}
				else
				{
					while (alist->pivot->prev->data != prev_max)
					pslist_rotate(alist, -1, "rra");
				}
				ps_merge_stacks(alist, blist, prev_min);
				ft_printf("after merge\n");
				ps_printlists(alist, blist, &printmembs);
				if (prev_max < blist->max)
					prev_max = blist->max;
				if (prev_min < blist->min)
					prev_min = blist->min;
			}
			else
			{
				ps_printlists(alist, blist, &printmembs);
				if (is_ordered(alist))
				{
					while (alist->pivot->data != alist->min)
						pslist_rotate(alist, 1, "ra");
				}
				ps_merge_stacks(alist, blist, prev_min);
				ft_printf("after merge\n");
				ps_printlists(alist, blist, &printmembs);
				prev_max = blist->max;
				prev_min = blist->min;
			}
			totalplaced += save / 10;
			i = 0;
			//while (i++ < totalplaced)
			//	pslist_rotate(alist,1, "ra");
			ps_printlists(alist, blist, &printmembs);
			ft_printf("number of operations was %d\n", counter);
			if (is_ordered(alist))
				break ;
	}
			
			//ps_printlists(alist, blist, &printmembs);
}


int	closest_gap_forward(t_pslist *list)
{
	int piv;
	int next;
	int count;
	t_psnode *cur;

	count = 0;
	cur = list->pivot;
	piv = cur->data;
	next = cur->next->data;
	while (next - piv == 1 || (piv == list->max && next == list->min))
	{
		cur = cur->next;
		piv = cur->data;
		next = cur->next->data;
		count++;
	}
	return (count);
}

int	closest_gap_backward(t_pslist *list)
{
	int piv;
	int prev;
	int count;
	t_psnode *cur;

	count = 0;
	cur = list->pivot;
	piv = cur->data;
	prev = cur->prev->data;
	while (piv - prev == 1 || (piv == list->min && prev == list->max))
	{
		cur = cur->prev;
		piv = cur->data;
		prev = cur->prev->data;
		count++;
	}
	return (count);
}

void	closest_gap(t_pslist *list)
{
	int count_front;
	int count_back;

	count_front = closest_gap_forward(list);
	count_back = closest_gap_backward(list);

}

void	ps_merge_stacks(t_pslist *alist, t_pslist *blist, int prev_min)
{
	while (blist->len)
	{
		while (blist->len && alist->pivot->prev->data < blist->pivot->data)
		{
			//ps_printlists(alist, blist, &printmembs);
			pslist_push_top(alist, blist, "pa");
			counter++;
		}

		while (blist->len && alist->pivot->data != prev_min && alist->pivot->prev->data > blist->pivot->data)
		{
			//ps_printlists(alist, blist, &printmembs);
			pslist_rotate(alist, -1, "rra");
			counter++;
		}
		if (alist->pivot->data == prev_min)
			break;
	}
	if (blist->len)
		dumpable(alist, blist);
	ft_printf("number of operations was %d\n", counter);
	//ps_printlists(alist, blist, &printmembs);
}

void	ps_merge_swap(t_pslist *alist, t_pslist *blist)
{
	while (blist->len)
	{
		while (blist->len && ((blist->pivot->data == blist->max && alist->pivot->data == alist->min) || alist->pivot->data == blist->pivot->data + 1))
		{
			//ps_printlists(alist, blist, &printmembs);
			pslist_push_top(alist, blist, "pa");
			counter++;
		}

		while (blist->len && (alist->pivot->data != blist->pivot->data + 1))
		{
			//ps_printlists(alist, blist, &printmembs);
			pslist_rotate(alist, -1, "rra");
			counter++;
		}
		if (!blist->len ||(blist->pivot->next != blist->pivot && blist->pivot-> data < blist->pivot->next->data))
			break;
	}
	ft_printf("number of operations was %d\n", counter);
	//ps_printlists(alist, blist, &printmembs);
}

