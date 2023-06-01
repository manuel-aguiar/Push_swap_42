/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_buckets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:29:36 by marvin            #+#    #+#             */
/*   Updated: 2023/04/25 10:29:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
int find_end_of_bucket(t_pslist *list, int min, int max)
{
	int countpos;
	int countneg;
	t_psnode *cur;

	countpos = 0;
	countneg = 0;
	cur = list->pivot;
	while (!(in_bucket(cur->data, min, max) && !in_bucket(cur->prev->data, min, max))
	&& countpos < list->len + 1)
	{
		cur = cur->next;
		countpos++;
	}
	if (countpos >= list->len)
		return (0);
	if (countpos > list->len / 2)
		return (countpos - list->len);
	return (countpos);
}

void move_to_end_of_bucket(t_pslist *list, int min, int max)
{
	int move;


	move = find_end_of_bucket(list, min, max);
	printf("calling bucket move, move is %d\n", move);
	if (!move)
		return ;
	if (move > 0)
	{
		while (move--)
		{
			pslist_rotate(list, 1, "rb");
			printf("end of bucket rotate\n");
			counter++;
		}
	}
	if (move < 0)
	{
		while (move++)
		{
			pslist_rotate(list, -1, "rrb");
			printf("end of bucket reverse rotate\n");
			counter++;
		}
	}
}

static int counter;

int     bucket_size(int divisor, int total)
{
    return (total / divisor);
}

int     in_bucket(int target, int min, int max)
{
    return ((target >= min && target < max));
}

void	get_b_max_on_top(t_pslist *blist)
{
	int i;
	t_psnode *cur;

	i = 0;
	cur = blist->pivot;
	while (cur->data != blist->max)
	{
		//ft_printf("cur->data %d, blist max %d\n", cur->data, blist->max);
		cur = cur->next;
		i++;
	}
	//printf("%d blist max, i is %d\n", blist->max, i);
	if (i <= blist->len / 2)
	{
		while (i--)
		{
			pslist_rotate(blist, 1, "rb");
			counter++;
		}
	}
	else
	{
		i = blist->len - i;
		while (i--)
		{
			pslist_rotate(blist, -1, "rrb");
			counter++;
		}
	}
}

void 	find_b_place(t_pslist *blist, int target)
{
	t_psnode *cur;
	int i;

	if (target <= blist->min || target >= blist->max)
		get_b_max_on_top(blist);
	else
	{
		i = 0;
		cur = blist->pivot;
		while(!(cur->prev->data > target && cur->data < target))
		{
			cur = cur->next;
			i++;
		}
		if (i <= blist->len / 2)
		{
			while (i--)
			{
				pslist_rotate(blist, 1, "rb");
				counter++;
			}
		}
		else
		{
			i = blist->len - i;
			while (i--)
			{
				pslist_rotate(blist, -1, "rrb");
				counter++;
			}
		}
	}
}

void	get_a_max_on_top(t_pslist *blist)
{
	int i;
	t_psnode *cur;

	i = 0;
	cur = blist->pivot;
	while (cur->data != blist->max)
	{
		//ft_printf("cur->data %d, blist max %d\n", cur->data, blist->max);
		cur = cur->next;
		i++;
	}
	//printf("%d blist max, i is %d\n", blist->max, i);
	if (i <= blist->len / 2)
	{
		while (i--)
		{
			pslist_rotate(blist, 1, "ra");
            counter++;
		}
	}
	else
	{
		i = blist->len - i;
		while (i--)
		{
			pslist_rotate(blist, -1, "rra");
            counter++;
		}
	}
}

void 	put_target_to_bottom(t_pslist *blist, int target)
{
	t_psnode *cur;
	int i;

    i = 0;
    cur = blist->pivot;
    while(cur->prev->data != target)
    {
        cur = cur->next;
        i++;
    }
    if (i <= blist->len / 2)
    {
        while (i--)
        {
            pslist_rotate(blist, 1, "ra");
            counter++;
        }
    }
    else
    {
        i = blist->len - i;
        while (i--)
        {
            pslist_rotate(blist, -1, "rra");
            counter++;
        }
    }
}



int find_closest_in_bucket(t_pslist *list, int min, int max)
{
	t_psnode *cur;
	int countpos;
	int countneg;

	countpos = 0;
	countneg = 0;
	cur = list->pivot;
	while (!in_bucket(cur->data, min, max))
	{
		cur = cur->next;
		countpos++;
	}
	cur = list->pivot;
	while (!in_bucket(cur->data, min, max) && -countneg < countpos)
	{
		cur = cur->prev;
		countneg--;
	}
	if (-countneg >= countpos)
		return (countpos);
	return (countneg);
}



void pushbucket(t_pslist *alist, t_pslist *blist, int min, int max)
{
    int size;
	int closest;
    size = max - min;

    while (size--)
    {
		closest = find_closest_in_bucket(alist, min, max);
		if (closest < 0)
		{
			while (closest++ < 0)
			{
				pslist_rotate(alist, -1, "rra");
				counter++;
			}
		}
		else if (closest > 0)
		{
			while (closest-- > 0)
			{
				pslist_rotate(alist, 1, "ra");
				counter++;
			}
		}
        pslist_push_top(blist, alist, "pb");
		//ps_printlists(alist, blist, &printmembs);
        counter++;
    }
}




void ps_buckets(t_pslist *alist, t_pslist *blist, int bucksize, int total)
{
    static int start;
    int end;

    if (start >= total)
	{
		start = 0;
        return ;
	}
    end = start + bucksize;
    if (start + bucksize > total)
        end = total;

    pushbucket(alist, blist, start, end);
    start += bucksize;
    //ps_printlists(alist, blist, &printmembs);
    ft_printf("total ops is %d\n", counter);
    ft_printf("total radix %d\n", total_radix_ops(total));
    ps_buckets(alist, blist, bucksize, total);


}



void ps_buckets_to_a(t_pslist *alist, t_pslist *blist, int bucksize, int total)
{

	static int buckets_placed;
	int begin;
    int end;

    if (total - (buckets_placed) * bucksize < 0)
	{
		buckets_placed = 0;
		printf("start %d, total %d", buckets_placed, total);
        return ;
	}
    end = total - (buckets_placed * bucksize);
	begin = end - bucksize;
    if (end - bucksize < 0)
        begin = 0;

	printf("pushing bucketsize %d, min %d, max %d\n", bucksize, begin, end);
    pushbucket(alist, blist, begin, end);
    buckets_placed++;
    //ps_printlists(alist, blist, &printmembs);
    ft_printf("total ops is %d\n", counter);
    ft_printf("total radix %d\n", total_radix_ops(total));
    ps_buckets_to_a(alist, blist, bucksize, total);


}


void test_bench(t_pslist *alist, t_pslist *blist, int total)
{
	int div;


	div = 2;

	ps_buckets(alist, blist, total / div, total);
	printf("pushing to a 1st time\n");
	div *= 2;
	ps_buckets_to_a(blist, alist, total / div, total);
	printf("pushing to B 2nd time\n");
	div *= 2;

	ps_buckets(alist, blist, total / div, total);
	printf("pushing to a 2nd time\n");
	ps_buckets_to_a(blist, alist, 1, total);
}

/*
void test_bench(t_pslist *alist, t_pslist *blist, int total)
{
	//ps_buckets_dumpfast(alist, blist, total / 5, total);
	int div;
	int stop;

	stop = 0;
	div = 4;
	while (total / div > 30 && !stop)
	{
		ps_buckets(alist, blist, total / div, total);
		printf("pushing to a 1st time\n");
		div *= 2;
		ps_buckets_to_a(blist, alist, total / div, total);
		printf("pushing to B 2nd time\n");
		div *= 2;
	}
	ps_buckets(alist, blist, total / div, total);
	printf("pushing to a 2nd time\n");
	ps_buckets_to_a(blist, alist, 1, total);
}
*/



