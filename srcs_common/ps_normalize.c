/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_normalize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:32:58 by marvin            #+#    #+#             */
/*   Updated: 2023/05/10 09:32:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static int	ascending(int a, int b)
{
	 return (a > b);
}

static int	copy_icplist_to_array(t_icplist *list, int **place)
{
	t_icpnode	*cur;
	int			*arr;
	int			len;
	int			i;

	len = list->len;
	arr = malloc(sizeof(int) * list->len);
	if (!arr)
		return (0);
	cur = list->pivot;
	i = 0;
	while (i < len)
	{
		arr[i] = cur->data;
		cur = cur->next;
		i++;
	}
	*place = arr;
	return (1);
}

static int	check_sorted_dups(int *sorted, int len)
{
	int	i;

	i = 0;
	while (i < len - 1)
	{
		if (sorted[i] == sorted[i + 1])
			return (0);
		i++;
	}
	return (1);
}

static int	normalize_list(t_icplist *list)
{
	t_icpnode	*cur;
	int			*sorted;
	int			len;
	int			i;

	if (!copy_icplist_to_array(list, &sorted))
		return (0);
	len = list->len;
	if(!tim_sort(sorted, len, &ascending) || !check_sorted_dups(sorted, len))
	{
		ft_free_set_null(&sorted);
		return (0);
	}
	cur = list->pivot;
	i = 0;
	while (i++ < len)
	{
		cur->data = bin_srch(sorted, len, cur->data, &ascending);
		cur = cur->next;
	}
	free(sorted);
	return (1);
}

int	ps_normalize(t_icplist **final)
{
	if (!normalize_list(*final))
	{
		icplist_destroy(final, 0);
		return (0);
	}
	return (1);
}
