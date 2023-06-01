/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_preprocess.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:28:31 by marvin            #+#    #+#             */
/*   Updated: 2023/04/20 11:28:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*

static int checkdups(int size, int *arr, int target)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (target == arr[i])
			return (0);
		i++;
	}
	return (1);
}


static void set_and_sort_check(int *arr, int index, int target, int *check)
{
	arr[index] = target;
	if (!index)
		return ;
	if (arr[index] < arr[index - 1])
		*check = 1;
}

static int prepare_dumb_arr_hash(int ***arr, t_ihs_table **table, int size)
{
	*arr = ft_calloc(sizeof(**arr), size);
	if (!*arr)
		return (malloc_failed());
	*table = ihs_init_table(size);
	if (!*table)
	{
		ft_free_set_null(arr);
		return (malloc_failed());
	}
	return (1);
}

static int arrtoi_freesplitforthedumb(int ***res, int size, char **args)
{
	int **arr;
	int **dumb_split;
	t_ihs_table	*table;

	if(!prepare_dumb_arr_hash(&arr, &table, size))
		return (malloc_failed());

}

static int arrtoi_naivedups(int **res, int size, char **args)
{
	int	*arr;
	int	i;
	int	num;
	int	check;

	arr = malloc(size * sizeof(*arr));
	if (!arr)
		return (malloc_failed());
	check = 1;
	i = 0;
	while (i < size)
	{
		if (ft_atoiable(args[i], &num) && checkdups(i, arr, num))
			arr[i++] = num;
		else
		{
			check = 0;
			break ;
		}
	}
	if (!check)
		ft_free_set_null(&arr);
	*res = arr;
	return (check);
}

static int prepare_arr_and_hash(int **arr, t_ihs_table **table, int size)
{
	*arr = malloc(size * sizeof(*arr));
	if (!*arr)
		return (malloc_failed());
	*table = ihs_init_table(size);
	if (!*table)
	{
		ft_free_set_null(arr);
		return (malloc_failed());
	}
	return (1);
}

static int arrtoi_tabledups(int **res, int size, char **args)
{
	int			*arr;
	int			i;
	int			num;
	t_ihs_table	*table;
	int			check;

	if (!prepare_arr_and_hash(&arr, &table, size))
		return (malloc_failed());
	check = 1;
	i = 0;
	while (i < size)
	{
		if (ft_atoiable(args[i], &num) && ihs_insert(table, num))
			arr[i++] = num;
		else
		{
			check = 0;
			break ;
		}
	}
	ihs_free_table(&table);
	if (!check)
		ft_free_set_null(&arr);
	*res = arr;
	return (check);
}

int ps_preprocess(int **res, int ac, char **av)
{
	int check;

	if (ac > MAGIC_SIZE)
		check = arrtoi_tabledups(res, ac, av);
	else
		check = arrtoi_naivedups(res, ac, av);
	if (!check)
		ft_free_set_null(res);
	return (check);
}*/
