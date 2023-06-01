/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_stack_communication.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:24:39 by marvin            #+#    #+#             */
/*   Updated: 2023/05/10 11:24:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	num_inst_equiv(t_ps_stack *send, t_ps_stack *receive, int command)
{
	if (command == send->codes.sa_num)
		return (receive->codes.sb_num);
	if (command == send->codes.sb_num)
		return (receive->codes.sa_num);
	if (command == send->codes.ra_num)
		return (receive->codes.rb_num);
	if (command == send->codes.rb_num)
		return (receive->codes.ra_num);
	if (command == send->codes.rra_num)
		return (receive->codes.rrb_num);
	if (command == send->codes.rrb_num)
		return (receive->codes.rra_num);
	if (command == send->codes.pa_num)
		return (receive->codes.pb_num);
	if (command == send->codes.pb_num)
		return (receive->codes.pa_num);
	return (0);
}

int	num_combo_equiv(t_ps_stack *send, t_ps_stack *receive, int command)
{
	if (command == send->codes.sa_num
	|| command == send->codes.sb_num)
		return (receive->codes.ss_num);
	if (command == send->codes.ra_num
	|| command == send->codes.rb_num)
		return (receive->codes.rr_num);
	if (command == send->codes.rra_num
	|| command == send->codes.rrb_num)
		return (receive->codes.rrr_num);
	return (0);
}

int	num_inst_reverse(t_ps_stack *send, t_ps_stack *receive, int command)
{
	if (command == send->codes.sa_num)
		return (send->codes.sa_num);
	if (command == send->codes.sb_num)
		return (send->codes.sb_num);
	if (command == send->codes.ra_num)
		return (send->codes.rra_num);
	if (command == send->codes.rb_num)
		return (send->codes.rrb_num);
	if (command == send->codes.rra_num)
		return (send->codes.ra_num);
	if (command == send->codes.rrb_num)
		return (send->codes.rb_num);
	if (command == send->codes.pa_num)
		return (receive->codes.pb_num);
	if (command == send->codes.pb_num)
		return (receive->codes.pa_num);
	if (command == send->codes.ss_num)
		return (receive->codes.ss_num);
	if (command == send->codes.rr_num)
		return (send->codes.rrr_num);
	if (command == send->codes.rrr_num)
		return (send->codes.rr_num);
	return (0);
}

void	print_command(int command)
{
	if (command == 1)
		ft_printf("sa  ");
	if (command == 2)
		ft_printf("sb  ");
	if (command == 3)
		ft_printf("ss  ");
	if (command == 4)
		ft_printf("pa  ");
	if (command == 5)
		ft_printf("pb  ");
	if (command == 6)
		ft_printf("ra  ");
	if (command == 7)
		ft_printf("rb  ");
	if (command == 8)
		ft_printf("rr  ");
	if (command == 9)
		ft_printf("rra  ");
	if (command == 10)
		ft_printf("rrb  ");
	if (command == 11)
		ft_printf("rrr  ");
}

void	print_command_nbr(int command)
{
	ft_putnbr(command);
	ft_printf("  ");
}
