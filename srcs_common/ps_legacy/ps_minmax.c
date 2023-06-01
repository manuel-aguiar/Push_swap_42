/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_plays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:57:56 by marvin            #+#    #+#             */
/*   Updated: 2023/04/20 15:57:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void minmax_add(t_pslist *list, int data)
{
    if (list->min == -1 || data < list->min)
        list->min = data;
    if (list->max == -1 || data > list->max)
        list->max = data;
}

void    minmax_del(t_pslist *list, int data)
{
    t_psnode *cur;

    if (list->len == 0)
    {
        list->min = -1;
        list->max = -1;
    }
	if (data != list->min && data != list->max)
		return ;
    else
    {
        list->min = -1;
        list->max = -1;
        minmax_add(list, list->pivot->data);
        cur = list->pivot->next;
        while (cur != list->pivot)
        {
            minmax_add(list, cur->data);
            cur = cur->next;
        }
    }
}



/*
void    printmulti(char *str, int times)
{
    while (times--)
        printf("%s\n", str);
}*/

/*

int rotatable(t_pslist *list)
{
    t_psnode *node;
    int count;
    int new_pivot;

    if (list->len == 1)
        return (1);
    node = list->pivot;
    count = 0;
    while (node->next != list->pivot)
    {
        //printf("comparing cur %d with next %d, list->min %d, list->max %d\n", node->data, node->next->data, list->min, list->max);
        if (node->next->data == node->data + 1)
            count++;
        else if (node->next->data < node->data && node->data == list->max && node->next->data == list->min)
        {
            count++;
            new_pivot = count;
        }
        else
            return (0);
        node = node->next;
    }
    if (new_pivot > list->len / 2)
    {
        pslist_rotate(list, new_pivot - list->len);
        return (new_pivot - list->len);
    }
    else
    {
        pslist_rotate(list, new_pivot);
        return (new_pivot);
    }
}*/
