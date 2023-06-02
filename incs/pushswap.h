/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:37:46 by marvin            #+#    #+#             */
/*   Updated: 2023/04/20 11:37:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H

# define PUSHSWAP_H

# include "libft.h"
# include <stdlib.h>
# include <stdint.h>

/*# define MAGIC_SIZE 200
# define MAGIC_NORM 50
# define SORT_SMALL 30*/
# define INSORT_TO_A 20
# define INSORT_TO_B INSORT_TO_A / 2
# define PUSHBUCKET_LIM 0
# define TRUE 1
# define FALSE 0


#include <stdio.h>

typedef struct s_inst_code
{
	int		sa_num;
	int		sb_num;
	int		ss_num;
	int		pa_num;
	int		pb_num;
	int		ra_num;
	int		rb_num;
	int		rr_num;
	int		rra_num;
	int		rrb_num;
	int		rrr_num;
} t_inst_code;

typedef struct s_ps_stack
{
	t_icplist	*list;
	t_idmlist 	*save_plays;
	t_inst_code codes;
	char		push_name[4];
	char		swap_name[4];
	char		rotate_name[4];
	char		revrot_name[5];
	char		swap_combo[4];
	char		rotate_combo[4];
	char		revrot_combo[5];
	int			my_swap_num;
	int			my_rot_num;
	int			my_revrot_num;
	int			my_push_num;
	int			ascending;
	int			op_counter;
	int			trial_mode;
} t_ps_stack;


enum e_play_options
{
	O_PRINT = 1 << 0,
	O_COUNT = 1 << 1,
	O_SAVE = 1 << 2,
	O_REVERSE = 1 << 3,
	O_BUF = 1 << 4,
	O_COMBO = 1 << 5,
};

/* pushswap list is a circular doubly linekd list with a memory pool
all functions i ahve on libft apply except the structs and initializers will
be different

list min and max will be set to -1 upon initialization as we will use only
number 0 and above"

*/

/*push_swap_main.c*/
int			pushswap(int ac, char **av);

/* ps_preprocess.c*/
int			ps_preprocess(t_icplist **final, int ac, char **av);

/* ps_preprocess_utils.c*/
int			ps_valid_char(char c);
int			wordnum(char *str);
int			ps_atoi_overf(int res, char next, int *sign);
int			ps_atoiable(char **arg, int *placenum);


/* ps_normalize.c*/
int			ps_normalize(t_icplist **final);

/*ps_output.c*/
void		void_putstr(void *str);
void		clean_putstr(void *str);
void		printmembs(int num);
void		ps_printlists(t_icplist *a_list, t_icplist *b_list, void (*pnt)(int));

/*ps_messages.c - error messages and functions*/
int			ok_message(void);
int			ko_message(void);
int			error_msg(void);
int			malloc_failed(void);

/*ps_stack_setup.c*/
void		setup_stack_a(t_ps_stack *a);
void		setup_stack_b(t_ps_stack *b);
void		setup_move_codes(t_inst_code *code);

/*ps_check_sort.c*/
int			bucket_is_sorted(t_ps_stack *stack, int min, int max);
int			final_sort_check(t_ps_stack *a_stack, t_ps_stack *b_stack, int total, int print);

/* ps_plays.c*/
int			pslist_swap_top(t_ps_stack *stack, int options);
int			pslist_push_top(t_ps_stack *to, t_ps_stack *from, int options);
int			pslist_rotate(t_ps_stack *stack, int rotate, int options);

/* ps_plays_options.c*/
int			save_command(t_ps_stack *stack, int command);
void		ps_manage_options(t_ps_stack *stack, int options, char *cmd, int cmd_num);

/* ps_plays_goto.c*/
void 		go_to_target_swap(t_ps_stack *stack, int target, int min, int max);
void		go_to_intersection(t_ps_stack *stack, int min, int max, int options);
void		go_to_endofbucket(t_ps_stack *stack, int min, int max, int options);
void		go_to_bucket_ends(t_ps_stack *stack, int min, int max, int options);
void		go_to_bucket_begins(t_ps_stack *stack, int min, int max, int options);

/* ps_plays_find.c*/
int			find_exact_target(t_ps_stack *stack, int target);
int			find_closest_in_bucket(t_ps_stack *stack, int min, int max);
int			find_mid_intersection(t_ps_stack *stack, int min, int max);
int			find_bucket_begins(t_ps_stack *stack, int min, int max);
int			find_bucket_ends(t_ps_stack *stack, int min, int max);

/*ps_play_find_utils.c*/
int			in_bucket(int target, int min, int max);
int			is_target(int target, int test);
int   		members_in_bucket(t_ps_stack *stack, int min, int max);
int			full_list_is_bucket(t_ps_stack *stack, int min, int max);
int			last_sorted_number(t_ps_stack *stack, int start, int end);

/*ps_plays_compound.c*/
void		pushbucket(t_ps_stack *from, t_ps_stack *to, int min, int max);
void		insertion_sort_push(t_ps_stack *from, t_ps_stack *to, int start, int end);
void 		swap_when_pushing(t_ps_stack *stack, int min, int max);
void 		swap_when_inserting(t_ps_stack *stack, int target, int min, int max);

/*ps_plays_supermoves.c*/
void		super_swap(t_ps_stack *a_stack, t_ps_stack *b_stack, int min, int max);
void		super_rotate(t_ps_stack *a_stack, t_ps_stack *b_stack);
void		super_revrot(t_ps_stack *a_stack, t_ps_stack *b_stack);

/*ps_plays_pushbucket_div.c*/
void    	pushbucket_divide(t_ps_stack *from, t_ps_stack *to, int min, int max);
void    	pushbucket_divide_col(t_ps_stack *from, t_ps_stack *to, int min, int max);

/* algos */
/*ps_quicksort.c*/
void		quicksort_a(t_ps_stack *a_stack, t_ps_stack *b_stack, int start, int end);
void		quicksort_b(t_ps_stack *a_stack, t_ps_stack *b_stack, int start, int end);

/*ps_cocktail_best_entry.c*/
int			best_cocktail_entry(t_ps_stack *stack, int len);

/*ps_cocktail_best_entry_mv.c*/
int 		get_stack_to_best_entry(t_ps_stack *stack, int min, int max, int options);

/*ps_cocktail_solver.c*/
void		stack_cocktail(t_ps_stack *stack, int min, int max, int options);

/*ps_cocktail_solver_utils.c*/
void 		pushswap_sort_two(t_ps_stack *stack, int options);
void		cocktail_two(t_ps_stack *stack, int min, int max, int options);
void		pushswap_sort_three(t_ps_stack *stack, int options);

/*ps_cocktail_parallel.c*/
void		parallel_cocktail(t_ps_stack *lead, t_ps_stack *follow, int min, int max);

/*ps_insertion_minmax.c*/
void		insertion_minmax(t_ps_stack *from, t_ps_stack *to, int min, int max);

/*ps_insertion_minmax_utils.c*/
int			closest_two_target(t_ps_stack *stack, int min, int max, int *is_max);
int			find_bucket_end_back(t_ps_stack *stack, int min, int max);

/* ps_execute_ops.c*/
int			execute_single(t_ps_stack *stack, t_ps_stack *other, int command, int options);
int			execute_combo(t_ps_stack *stack, t_ps_stack *other, int command, int options);
char		*inst_reverse(t_ps_stack *stack, t_ps_stack *other, int command);
int			execute_list_rev(t_ps_stack *a_stack, t_ps_stack *b_stack, t_idmlist *ops, int options);
int			execute_list(t_ps_stack *a_stack, t_ps_stack *b_stack, t_idmlist *ops, int options);

/*ps_trials_a_stack.c*/
void		a_stack_double_ins(t_ps_stack *a_stack, t_ps_stack *b_stack, int min, int max);
void		a_stack_double_cocktail(t_ps_stack *a_stack, t_ps_stack *b_stack, int min, int max);
void		a_stack_trials(t_ps_stack *a_stack, t_ps_stack *b_stack, int min, int max);

/*ps_trials_b_stack.c*/
void		b_stack_insertion_minmax(t_ps_stack *a_stack, t_ps_stack *b_stack, int min, int max);
void 		b_stack_straight_ins(t_ps_stack *a_stack, t_ps_stack *b_stack, int min, int max);
void 		b_stack_double_cocktail(t_ps_stack *a_stack, t_ps_stack *b_stack, int min, int max);
void 		b_stack_trials(t_ps_stack *a_stack, t_ps_stack *b_stack, int min, int max);

/*ps_trials_utils.c*/
void		trial_judge(t_ps_stack *challenger, t_idmlist **record, int first_try);
void		trial_minmax(t_ps_stack *challenger, t_idmlist **record);

/*ps_parellelize.c*/
void		intersect_plays(t_idmlist *combo, t_ps_stack *a_stack, t_ps_stack *b_stack);
void		merge_plays(t_ps_stack *receiver, t_ps_stack *sender);

/*ps_parellelize_lists.c*/
t_idmnode	*idmlist_retrieve_head(t_idmlist **list);
void		idmlist_node_to_tail(t_idmlist *list, t_idmnode *new_node);
void		idmlist_del_head_destroy(t_idmlist **list);

/*ps_stack_communication.c*/
int			num_inst_equiv(t_ps_stack *send, t_ps_stack *receive, int command);
int			num_combo_equiv(t_ps_stack *send, t_ps_stack *receive, int command);
int			num_inst_reverse(t_ps_stack *send, t_ps_stack *receive, int command);
void		print_command(int command);
void		print_command_nbr(int command);













#endif
