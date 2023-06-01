/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:02:22 by marvin            #+#    #+#             */
/*   Updated: 2023/04/27 14:02:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	ok_message(void)
{
	ft_printf("OK\n");
	return (1);
}

int	ko_message(void)
{
	ft_printf("KO\n");
	return (1);
}

int	error_msg(void)
{
	ft_putstr_fd("Error\n", 2);
	return (0);
}

int	malloc_failed(void)
{
	ft_putstr_fd("Malloc failed\n", 2);
	exit(EXIT_FAILURE);
}
