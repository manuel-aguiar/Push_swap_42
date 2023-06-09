
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
SRC_PATH	=		srcs
COMMON_PATH	=		srcs_common
PS_PATH		=		srcs_ps
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

FILES_B		=		ps_checker_main_bonus.c		\
					ps_checker_counter_bonus.c 	\
					ps_checker_utils_bonus.c

FILES_PS	=		push_swap_main.c


SRCS_COMMON := 		$(addprefix $(SRC_PATH)/, $(addprefix $(COMMON_PATH)/, $(FILES)))
SRCS_PS 	:= 		$(addprefix $(SRC_PATH)/, $(addprefix $(PS_PATH)/, $(FILES_PS)))
SRCS_B		:= 		$(addprefix $(SRC_PATH)/, $(addprefix $(BONUS_PATH)/, $(FILES_B)))


OBJS		=		$(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o,$(SRCS_COMMON))
OBJS_PS		=		$(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o,$(SRCS_PS))
OBJS_B 		=		$(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o,$(SRCS_B))

INCS		= 		-I$(INC_PATH) -I$(LIB_PATH)/$(LIB_INC_P)

all: $(NAME)

$(NAME): message $(LIBFT) $(OBJS) $(OBJS_PS)
	@$(CC) $(FLAGS) $(OBJS) $(OBJS_PS) $(INCS) -o $(NAME) $(ADD_LIB) $(LIB_PATH)/$(LIBFT)
	@echo Program $(NAME) ready!!

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

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
	@if [ -d "$(OBJ_PATH)" ]; then \
        rm -rf $(OBJ_PATH); \
    fi
	@make clean -C $(LIB_PATH)
	@echo Objects successfully deleted!

fclean: clean
	@echo Deleting libft.a...
	@if [ -n "$(wildcard  $(NAME))" ]; then \
        $(RM) $(NAME); \
    fi
	@if [ -n "$(wildcard  $(BONUS))" ]; then \
        $(RM) $(BONUS); \
    fi
	@if [ -n "$(wildcard  $(LIB_PATH)/$(LIBFT))" ]; then \
        $(RM) $(LIB_PATH)/$(LIBFT); \
    fi
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
