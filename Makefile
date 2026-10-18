# ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ LAYOUT ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

DEFAULT			= \033[0m
GREEN			= \033[1;32m
CYAN			= \033[1;36m


define ANIMATION_FRAME
				@for frame in ⠋ ⠙ ⠹ ⠸ ⠼ ⠴ ⠦ ⠧ ⠇ ⠏; do \
				printf "$$frame $(1)...\r"; \
				sleep 0.02; \
				done; \
				printf "\n"
endef


# ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ VARIABLES ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

NAME =			push_swap
CHECKER =		checker

CC =			cc
CFLAGS =		-Wall -Wextra -Werror -I include -I $(LIB_DIR)include $(EXTRA_FLAGS)

SRC_DIR =		src/
OBJ_DIR =		obj/
LIB_DIR =		libft-extended/

LIB =			$(LIB_DIR)libft.a

SRC_COMMON =	parsing/numbers.c \
				stack/stack.c \
				stack/stack_utils.c \
				ops/engine.c \
				ops/table.c \
				utils/utils.c
SRC_PS =		main.c \
				parsing/options.c \
				ops/emit.c \
				ops/ops_push.c \
				ops/ops_swap.c \
				ops/ops_rotate.c \
				ops/ops_reverse.c \
				algo/dispatch.c \
				algo/small.c \
				algo/selection.c \
				algo/chunks.c \
				algo/radix.c \
				algo/turk/turk.c \
				algo/turk/push_to_b.c \
				algo/turk/target.c \
				algo/turk/cost.c \
				algo/turk/execute.c \
				bench/bench.c
SRC_CHECKER =	$(patsubst $(SRC_DIR)%,%,$(wildcard $(SRC_DIR)checker/*.c))

OBJ =			$(addprefix $(OBJ_DIR), $(SRC_COMMON:.c=.o) $(SRC_PS:.c=.o))
OBJ_CHECKER =	$(addprefix $(OBJ_DIR), $(SRC_COMMON:.c=.o) $(SRC_CHECKER:.c=.o))


# ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ RULES ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

all:			$(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(dir $@)
				@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJ)
				@make -s -C $(LIB_DIR) --no-print-directory
				$(call ANIMATION_FRAME,Building $(NAME) executable)
				@$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $@
				@printf "$(GREEN)✓$(DEFAULT) Built successfully $(NAME) ($(words $?)/$(words $(SRC_PS) $(SRC_COMMON)) files recompiled)\n"

check:			$(CHECKER)

$(CHECKER):		$(OBJ_CHECKER)
				@make -s -C $(LIB_DIR) --no-print-directory
				$(call ANIMATION_FRAME,Building $(CHECKER))
				@$(CC) $(CFLAGS) $(OBJ_CHECKER) $(LIB) -o $@
				@printf "$(GREEN)✓$(DEFAULT) Built successfully $(CHECKER) ($(words $?)/$(words $(SRC_CHECKER) $(SRC_COMMON)) files recompiled)\n"

clean:
				$(call ANIMATION_FRAME,Cleaning objects)
				@make -C $(LIB_DIR) clean --no-print-directory
				@rm -rf $(OBJ_DIR)

fclean:			clean
				$(call ANIMATION_FRAME,Removing executable and library)
				@rm -f $(NAME) $(CHECKER) $(LIB)

re:				fclean all

test:			all checker
				@./tests/errors.sh
				@for s in --simple --medium --complex --turk --adaptive; do \
				./tests/run.sh 5 30 $$s && ./tests/run.sh 100 10 $$s \
				&& ./tests/run.sh 500 3 $$s || exit 1; \
				done

100 500:		all checker
				@./tests/run.sh $@ 20

bench:			all checker
				@./tests/bench.sh

debug:
				@$(MAKE) fclean --no-print-directory
				@$(MAKE) all checker --no-print-directory EXTRA_FLAGS="-g3 -fsanitize=address,undefined"

help:
				@printf "Usage: make [target]\n"
				@printf "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
				@printf "$(CYAN)all$(DEFAULT)		- Build the executable $(NAME)\n"
				@printf "$(CYAN)checker$(DEFAULT)		- Build the executable $(NAME)\n"
				@printf "$(CYAN)clean$(DEFAULT)		- Clean up object files\n"
				@printf "$(CYAN)fclean$(DEFAULT)		- Clean up all object files and executable\n"
				@printf "$(CYAN)re$(DEFAULT)		- Rebuild the entire project\n"
				@printf "$(CYAN)test$(DEFAULT)		- Edge cases + every strategy on 5 / 100 / 500 values\n"
				@printf "$(CYAN)100/500$(DEFAULT)		- Sort 20 random sets of 100 / 500 values and report op counts\n"
				@printf "$(CYAN)bench$(DEFAULT)		- Operation counts per strategy (markdown table)\n"
				@printf "$(CYAN)debug$(DEFAULT)		- Rebuild with ASan + UBSan\n"
				@printf "$(CYAN)help$(DEFAULT)		- Show this help message\n"

.PHONY:			all check clean fclean re test 100 500 bench debug help
