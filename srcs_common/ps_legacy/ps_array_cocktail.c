/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_array_cocktail.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:37:19 by marvin            #+#    #+#             */
/*   Updated: 2023/04/28 11:37:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int		is_array_sorted(int *arr, int len, int ascending)
{
	int i;

	i = 1;
	while (i < len)
	{
		if ((ascending && arr[i] != arr[i - 1] + 1) \
		|| (!ascending && arr[i] != arr[i - 1] - 1))
			return (0);
		i++;
	}
	return (1);
}

static void	ps_swap(int *a, int *b, int *counter)
{
    int	temp;

    temp = *a;
    *a = *b;
    *b = temp;
	(*counter)++;
	printf("sa\n");
}

static int	ps_frontrun(int *arr, int len, int swapn, int *counter)
{
    int	i;

    i = swapn - 1;
	if (i < 0)
		i = 0;
	ft_print_arr(arr, len, &printmembs);
	printf("<- starting frontrun\n");
	if (arr[i] > arr[i + 1])
        ps_swap(&arr[i],&arr[i + 1], counter);
    while (i < (len - swapn - 2))
    {
        if (is_array_sorted(arr, len, 1))
		{
			(*counter) += i;
			while (i-- > 0)
				printf("rra <- reverse until index zero again\n");
			return (0);
		}
		(*counter)++;
        i++;
		printf("ra <-index is %d\n", i);
		ft_print_arr(arr, len, &printmembs);
		printf("\n");
		if (arr[i] > arr[i + 1] && i < len)
        	ps_swap(&arr[i],&arr[i + 1], counter);
		ft_print_arr(arr, len, &printmembs);
		printf("\n");
    }
    return (1);
}

static int	ps_backrun(int *arr, int len, int swapn, int *counter)
{
    int	j;

    j = (len - swapn - 1) - 1;
	ft_print_arr(arr, len, &printmembs);
	printf("<- starting backrun, starting index is %d\n", j);
    while (j > swapn)
    {
		(*counter)++;
        j--;
		printf("rra <- index is %d\n", j);
		if (arr[j] > arr[j + 1])
            ps_swap(&arr[j],&arr[j + 1], counter);
		ft_print_arr(arr, len, &printmembs);
		printf("<-array after potential swap\n");
    }
	if (is_array_sorted(arr, len, 1))
	{
		(*counter) += j;
		while (j-- > 0)
			printf("rra <- reverse until index zero again\n");
		return (0);
	}
    return (1);
}

int	ps_cocktail_counter(int *arr, int len)
{
    int	swapn;
    int	sorttoright;
    int	sorttoleft;
	int counter;

	counter = 0;
    swapn = 0;
    sorttoright = 1;
    sorttoleft = 0;
    while(swapn < (len / 2) && sorttoright)
    {
        if (sorttoright)
            sorttoleft = ps_frontrun(arr, len, swapn, &counter);
		else
			return (counter);
        sorttoright = 0;
        if (sorttoleft)
            sorttoright = ps_backrun(arr, len, swapn, &counter);
		else
			return (counter);
        sorttoleft = 0;
        swapn++;
    }
	return (counter);
}

static int target_index(int *arr, int len, int target)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (arr[i] == target)
			return (i);
		i++;
	}
	return (-1);
}

static int target_bucket(int *arr, int len, int min, int max)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (arr[i] >= min && arr[i] < max)
			return (i);
		i++;
	}
	return (-1);
}

int ps_insertion_counter(int *arr, int len, int min, int max)
{
	int i;
	int find;
	int counter;

	counter = 0;
	i = 0;
	ft_print_arr(arr, len, &printmembs);
	printf("\n");
	while (--max >= min)
	{
		find = target_index(arr, len, max);
		counter += (ABS((find - i)) + 1);
		printf("target is %d, at index %d\n", max, find);
		i = find;
		while (++find < len)
			arr[find - 1] = arr[find];
		arr[find - 1] = -1;

		len--;
		ft_print_arr(arr, len, &printmembs);
		printf("\n");
	}
	return (counter);
}

int		*from_list_to_arr(t_icplist *list, int *arr, int size)
{
	t_icpnode *cur;
	int i;

	cur = list->pivot;
	i = 0;
	while (i < size)
	{
		arr[i] = cur->data;
		cur = cur->next;
		i++;
	}
	return (arr);
}

int		*reverse_array(int *arr, int len)
{
	int i;
	int temp;

	i = 0;
	while (i < len / 2)
	{
		temp = arr[i];
		arr[i] = arr[len - i - 1];
		arr[len - i - 1] = temp;
		i++;
	}
	return (arr);
}

int		ps_mixed_helper(int *arr, int *helper, int len, int helperlen)
{
	int mid;
	int counter;

	counter = 0;
	reverse_array(helper, helperlen);
	ft_print_arr(helper, helperlen, &printmembs);
	printf("<- reversed helper array\n");
	if (!is_array_sorted(helper, helperlen, 1))
		counter += ps_cocktail_counter(helper, helperlen);
	if (!is_array_sorted(arr, len, 1))
		counter += ps_cocktail_counter(arr, len);
	counter += (helperlen);
	return (counter);
}

int 	ps_setting_helper(int *helper, int *helperlen, int len)
{
	int helplen;

	helplen = len / 2;
	*helperlen = helplen;
	helper[SORT_SMALL - 1] = len;
	helper[SORT_SMALL - 2] = helplen;
}

int		ps_mixed_counter(int *arr, int len, int min, int max)
{
	int helper[SORT_SMALL];
	int	i;
	int helperlen;
	int counter;
	int find;

	counter = 0;
	i = 0;
	ps_setting_helper(helper, &helperlen, len);
	while (helperlen > 0)
	{
		find = target_bucket(arr, len, min, min + helperlen);
		counter += (ABS((find - i)) + 1);
		i = find;
		helper[helperlen - 1] = arr[i];
		while (++find < len)
			arr[find - 1] = arr[find];
		arr[find - 1] = -1;
		helperlen--;
		len--;
	}
	helperlen = helper[SORT_SMALL - 2];
	len = helper[SORT_SMALL - 1] - helperlen;
	counter += (i + ps_mixed_helper(arr, helper, len, helperlen));
	return (counter);
}

void	ps_sort_really_small(t_icplist *to_sort, int min, int max)
{
	int arr[SORT_SMALL];
	int cocktail;
	int insertion;
	int mixed;
	int size;

	size = max - min;
	cocktail = ps_cocktail_counter(from_list_to_arr(to_sort, arr, size), size);
	insertion = ps_insertion_counter(from_list_to_arr(to_sort, arr, size), size, min, max);
	mixed = ps_mixed_counter(from_list_to_arr(to_sort, arr, size), size, min, max);
}

void cheapcopy(int *arr, int *copy, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		copy[i] = arr[i];
		i++;
	}
}


void	ps_sort_really_small_arr(int *arr, int len, int min, int max)
{
	int cocktail;
	int insertion;
	int mixed;
	int copy[len];

	int copycocktail[len];

	cheapcopy(arr, copy, len);
	cocktail = ps_cocktail_counter(copy, len);
	cheapcopy(copy, copycocktail, len);
	cheapcopy(arr, copy, len);
	reverse_array(copy, len);
	insertion = ps_insertion_counter(copy, len, min, max) + len;

	cheapcopy(arr, copy, len);
	mixed = ps_mixed_counter(copy, len, min, max);
	printf("cocktail operations %d\n", cocktail);
	printf("insertion operations %d\n", insertion);
	printf("mixed operations %d\n", mixed);
	ft_print_arr(copycocktail, len, &printmembs);
	printf("\n");
}

/*
int main(void)
{
	int arr[] = {17, 10, 23, 11, 6, 2, 1, 7, 15, 18, 14, 21, 3, 22, 8, 24, 16, 5, 12, 9, 19, 25, 4, 20, 13};
	int len = sizeof(arr) / sizeof(*arr);

	ps_sort_really_small_arr(arr, len, 1, 26);
	printf("\n");
	ft_print_arr(arr, len, &printmembs);
	printf("\n");
	return (0);
}*/

