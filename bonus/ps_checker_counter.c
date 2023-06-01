/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_checker_counter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:06:18 by marvin            #+#    #+#             */
/*   Updated: 2023/05/03 10:06:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap_checker.h"

void	set_counter_on_stack(t_pscount *counter, int len)
{
	counter->total_numbers = len;
	counter->total_count = 0;
	counter->sa_count = 0;
	counter->sb_count = 0;
	counter->ss_count = 0;
	counter->ra_count = 0;
	counter->rb_count = 0;
	counter->rr_count = 0;
	counter->rra_count = 0;
	counter->rrb_count = 0;
	counter->rrr_count = 0;
	counter->pa_count = 0;
	counter->pb_count = 0;
}

void	set_counter_total(t_pscount *counter)
{
	counter->total_count += counter->sa_count;
	counter->total_count += counter->sb_count;
	counter->total_count += counter->ss_count;
	counter->total_count += counter->ra_count;
	counter->total_count += counter->rb_count;
	counter->total_count += counter->rr_count;
	counter->total_count += counter->rra_count;
	counter->total_count += counter->rrb_count;
	counter->total_count += counter->rrr_count;
	counter->total_count += counter->pa_count;
	counter->total_count += counter->pb_count;
}

void	print_counter(t_pscount *counter)
{
	set_counter_total(counter);
	ft_printf("total size: %d\n", counter->total_numbers);
	ft_printf("total operations: %d\n", counter->total_count);
	ft_printf("sa count: %d\n", counter->sa_count);
	ft_printf("sb count: %d\n", counter->sb_count);
	ft_printf("ss count: %d\n", counter->ss_count);
	ft_printf("ra count: %d\n", counter->ra_count);
	ft_printf("rb count: %d\n", counter->rb_count);
	ft_printf("rr count: %d\n", counter->rr_count);
	ft_printf("rra count: %d\n", counter->rra_count);
	ft_printf("rrb count: %d\n", counter->rrb_count);
	ft_printf("rrr count: %d\n", counter->rrr_count);
	ft_printf("pa count: %d\n", counter->pa_count);
	ft_printf("pb count: %d\n", counter->pb_count);
}
