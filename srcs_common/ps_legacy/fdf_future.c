/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_future.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 22:02:01 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/05/07 00:08:59 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "libft.h"

typedef struct s_colour
{
    int *arr;
    struct s_colour *next;
    struct s_colour *prev;

} t_colour

typedef struct s_linelist
{
    int len;
    struct s_colour *head;
    struct s_colour *tail;

} t_linelist;


insert_head(t_linelist *list, int rgbdata)
{
    t_colour *node;

    node = init_node(rgbdata);
    list->tail->next = node;
    list->tail = node;
    (list->len)++;

}

int **my_map(fd)
{
    t_linelist *list;
    t_colour *node;

    int check;
    int *arr;
    char **split;
    int size;
    char *line;
    int **matrix;

    check = 1;
    line = (char *)1;
    while (line && check)
    {
        list = initialize();
        line = get_next_line(fd);
        split = split(line, &size);
        arr = malloc(sizeof(*arr) * size);
        i = 0;
        while (i < size)
        {
            arr[i] = atoi(split[i]);
            i++;
        }
        insert_at_list(list, arr);
        list = NULL;
    }
    matrix = malloc(sizeof(*matrix) * (list->len));
    j = 0;

    node = list->head;
    while (j < list->len)
    {
        matrix[j] = node->arr;
        node = node->next;
        j++;

    }
    destroy_list(list, NULL);
    return(matrix);
}


char **split(char *line, int *size)
{


    num_words = numberwords();
    *size = num_words;
}
*/