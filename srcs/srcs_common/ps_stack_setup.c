/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_stack_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:53:31 by marvin            #+#    #+#             */
/*   Updated: 2023/05/09 15:53:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	setup_move_codes(t_inst_code *code)
{
	code->sa_num = 1;
	code->sb_num = 2;
	code->ss_num = 3;
	code->pa_num = 4;
	code->pb_num = 5;
	code->ra_num = 6;
	code->rb_num = 7;
	code->rr_num = 8;
	code->rra_num = 9;
	code->rrb_num = 10;
	code->rrr_num = 11;
}

void	setup_stack_b(t_ps_stack *b)
{
	b->save_plays = NULL;
	ft_memcpy(b->push_name, "pa\n\0", sizeof(b->push_name));
	ft_memcpy(b->swap_name, "sb\n\0", sizeof(b->swap_name));
	ft_memcpy(b->rotate_name, "rb\n\0", sizeof(b->rotate_name));
	ft_memcpy(b->revrot_name, "rrb\n\0", sizeof(b->revrot_name));
	ft_memcpy(b->swap_combo, "ss\n\0", sizeof(b->swap_combo));
	ft_memcpy(b->rotate_combo, "rr\n\0", sizeof(b->rotate_combo));
	ft_memcpy(b->revrot_combo, "rrr\n\0", sizeof(b->revrot_combo));
	b->ascending = 0;
	b->op_counter = 0;
	b->trial_mode = 0;
	setup_move_codes(&(b->codes));
	b->my_swap_num = b->codes.sb_num;
	b->my_rot_num = b->codes.rb_num;
	b->my_revrot_num = b->codes.rrb_num;
	b->my_push_num = b->codes.pa_num;
}

void	setup_stack_a(t_ps_stack *a)
{
	a->save_plays = NULL;
	ft_memcpy(a->push_name, "pb\n\0", sizeof(a->push_name));
	ft_memcpy(a->swap_name, "sa\n\0", sizeof(a->swap_name));
	ft_memcpy(a->rotate_name, "ra\n\0", sizeof(a->rotate_name));
	ft_memcpy(a->revrot_name, "rra\n\0", sizeof(a->revrot_name));
	ft_memcpy(a->swap_combo, "ss\n\0", sizeof(a->swap_combo));
	ft_memcpy(a->rotate_combo, "rr\n\0", sizeof(a->rotate_combo));
	ft_memcpy(a->revrot_combo, "rrr\n\0", sizeof(a->revrot_combo));
	a->ascending = 1;
	a->op_counter = 0;
	a->trial_mode = 0;
	setup_move_codes(&(a->codes));
	a->my_swap_num = a->codes.sa_num;
	a->my_rot_num = a->codes.ra_num;
	a->my_revrot_num = a->codes.rra_num;
	a->my_push_num = a->codes.pb_num;
}
