/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap_check.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:58:51 by marvin            #+#    #+#             */
/*   Updated: 2023/05/03 09:58:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

typedef struct	s_pscount
{
	int	total_numbers;
	int	total_count;
	int	sa_count;
	int	sb_count;
	int	ss_count;
	int	ra_count;
	int	rb_count;
	int	rr_count;
	int	rra_count;
	int	rrb_count;
	int	rrr_count;
	int	pa_count;
	int	pb_count;
}	t_pscount;

/* ps_checker.c */
int		checker_solver(int ac, char **av);
void	ok_reaction(t_pscount *counter);
void	ko_reaction(t_ps_stack *a_stack, t_ps_stack *b_stack, \
t_pscount *counter);
void	stack_and_counter(t_ps_stack *a_stack, t_ps_stack *b_stack, \
t_pscount *counter, int *total_len);

/*  ps_checker_utils.c */
int		op_swap(t_ps_stack *a_stack, t_ps_stack *b_stack, char *op, t_pscount *counter);
int		op_reverse_rotation(t_ps_stack *a_stack, t_ps_stack *b_stack, char *op, t_pscount *counter);
int		op_rotation(t_ps_stack *a_stack, t_ps_stack *b_stack, char *op, t_pscount *counter);
int		distribute_operations(t_ps_stack *a_stack, t_ps_stack *b_stack, char *op, t_pscount *counter);
int		get_all_operations(t_ps_stack *a_stack, t_ps_stack *b_stack, t_pscount *counter);

/*  ps_checker_counter.c */
void	set_counter_on_stack(t_pscount *counter, int len);
void	set_counter_total(t_pscount *counter);
void	print_counter(t_pscount *counter);
