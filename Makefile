
## BUILD DETAILS

NAME 		=		push_swap
BONUS 		=		checker

CC 			= 		cc
## -Wall Wextra Werror
FLAGS 		= 		-Wall -Werror -Wextra
ADD_LIB 	= 		-L./$(LIB_PATH) -lft
RM 			=		rm
MAKE		=		make

## FOLDER PATH ##
INC_PATH	=		incs
SRC_PATH	=		srcs_common
SRC_PS_PATH	=		srcs_ps
BONUS_PATH	=		bonus
OBJ_PATH	=		objs

LIB_PATH	=		libft
LIB_INC_P	=		incs

## SOURCE LIBRARIES
LIBFT		=		libft.a

## SOURCE FILES ##
FILES		=		ps_preprocess.c 			\
					ps_preprocess_utils.c 		\
					ps_normalize.c 				\
					ps_stack_setup.c			\
					ps_stack_communication.c	\
					ps_output.c 				\
					ps_plays.c 					\
					ps_plays_options.c			\
					ps_plays_goto.c 			\
					ps_plays_find.c 			\
					ps_plays_find_utils.c 		\
					ps_plays_compound.c 		\
					ps_plays_supermoves.c		\
					ps_plays_pushbucket_div.c	\
					ps_cocktail_best_entry.c	\
					ps_cocktail_best_entry_mv.c	\
					ps_cocktail_solver.c		\
					ps_cocktail_solver_utils.c	\
					ps_cocktail_parallel.c		\
					ps_insertion_minmax.c		\
					ps_insertion_minmax_utils.c	\
					ps_check_sort.c 			\
					ps_execute_ops.c 			\
					ps_quicksort.c				\
					ps_parallelize.c			\
					ps_parallelize_lists.c		\
					ps_trials_a_stack.c			\
					ps_trials_b_stack.c			\
					ps_trials_utils.c			\
					ps_messages.c

FILES_B		=		checker_main.c				\
					ps_checker_counter.c 		\
					ps_checker_utils.c

FILES_PS	=		push_swap_main.c


SRCS_COMMON := 		$(addprefix $(SRC_PATH)/, $(FILES))
SRCS_PS 	:= 		$(addprefix $(SRC_PS_PATH)/, $(FILES_PS))
SRCS_B		:= 		$(addprefix $(BONUS_PATH)/, $(FILES_B))


OBJS		=		$(SRCS_COMMON:%.c=%.o)
OBJS_PS		=		$(SRCS_PS:%.c=%.o)
OBJS_B 		=		$(SRCS_B:%.c=%.o)

INCS		= 		-I$(INC_PATH) -I$(LIB_PATH)/$(LIB_INC_P)

all: $(NAME)
##@mkdir -p objs
##@mv $(OBJS) objs
##@mv $(OBJS_PS) objs

$(NAME): message $(LIBFT) $(OBJS) $(OBJS_PS)
	@$(CC) $(FLAGS) $(OBJS) $(OBJS_PS) $(INCS) -o $(NAME) $(ADD_LIB) $(LIB_PATH)/$(LIBFT)
	@echo Program $(NAME) ready!!

%.o : %.c
	@$(CC) $(FLAGS) $(INCS) -c $< -o $@

$(LIBFT):
	@echo Preparing Libft....
	@$(MAKE) -C $(LIB_PATH)

bonus: $(BONUS)

$(BONUS) : message $(LIBFT) $(OBJS) $(OBJS_B)
	@$(CC) $(FLAGS) $(OBJS) $(OBJS_B) $(INCS) -o $(BONUS) $(ADD_LIB) $(LIB_PATH)/$(LIBFT)
	@echo Program $(BONUS) ready!!

message:
	@echo Building program....

clean:
	@echo Removing object files.....
	@$(RM) $(OBJS)
	@$(RM) -r $(OBJ_PATH)
	@rmdir $(OBJ_PATH)
	@echo Objects successfully deleted!

fclean: clean
	@echo Deleting libft.a...
	$(RM) $(NAME)
	@echo Done!!

re: fclean all

.PHONY: clean fclean re message bonus

##COLOUR

CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
