/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:39:54 by marvin            #+#    #+#             */
/*   Updated: 2023/05/10 09:39:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	void_putstr(void *str)
{
	char	*new;
	int		i;

	new = (char *)str;
	write(1, new, (int)ft_strlen(new) - 1);
	i = 0;
	while ((i++ < 5 - (int)ft_strlen(new)))
		write(1, " ", 1);
}

void	clean_putstr(void *str)
{
	char	*new;

	new = (char *)str;
	write(1, new, ft_strlen(new));
}

void	printmembs(int num)
{
	ft_printf("%d   ", num);
}

void	ps_printlists(t_icplist *a_list, t_icplist *b_list, void (*pnt)(int))
{
	ft_printf("\nlist B: ");
	icplist_head_print(b_list, pnt);
	ft_printf("\n\nlist A: ");
	icplist_head_print(a_list, pnt);
	ft_printf("\n\n");
}
