#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/* ================================ INCLUDES ================================ */

# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

/* ================================== ENUM ================================= */

typedef enum e_strategy
{
	SIMPLE,
	MEDIUM,
	COMPLEX,
	TURK,
	ADAPTIVE
}	t_strategy;

typedef enum e_op
{
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR,
	OP_COUNT
}	t_op;

/* ================================ STRUCTURES ================================ */

typedef struct s_stack
{
	int				value;
	int				index;
	int				pos;
	int				target;
	int				cost_a;
	int				cost_b;
	struct s_stack	*next;
}					t_stack;

typedef struct s_stats
{
	int	count[OP_COUNT];
	int	total;
}		t_stats;

typedef struct s_config
{
	t_strategy	strategy;
	bool		bench_mode;
	double		disorder;
	t_stats		stats;
}				t_config;

typedef struct s_input
{
	int	*values;
	int	count;
}		t_input;

typedef void	(*t_sort_fn)(t_stack **a, t_stack **b, int size, t_config *cfg);

/* ========================== FUNCTION PROTOTYPES =========================== */

/* --- parsing/ --- */

bool		parse_options(int argc, char **argv, t_config *cfg, int *first);
bool		parse_numbers(int argc, char **argv, int first, t_input *in);

/* --- stack/ --- */

t_stack		*stack_new(int value);
void		stack_add_back(t_stack **lst, t_stack *new);
int			stack_size(t_stack *lst);
t_stack		*stack_last(t_stack *lst);
t_stack		*stack_before_last(t_stack *lst);
t_stack		*stack_from_input(const t_input *in);
void		free_stack(t_stack *stack);
void		index_stack(t_stack *a);
bool		is_sorted(t_stack *stack);
double		compute_disorder(t_stack *stack);

/* --- ops/engine.c: silent primitives, safe on empty / single stacks --- */

void		op_swap(t_stack **s);
void		op_push(t_stack **src, t_stack **dst);
void		op_rotate(t_stack **s);
void		op_reverse(t_stack **s);

/* --- ops/table.c: single table shared by push_swap and checker --- */

void		op_apply(t_op op, t_stack **a, t_stack **b);
int			op_from_name(const char *line);
char		*op_name(t_op op);

/* --- ops/emit.c + ops_*.c: apply + print + count (push_swap only) --- */

void		op_run(t_op op, t_stack **a, t_stack **b, t_config *cfg);
void		pa(t_stack **a, t_stack **b, t_config *cfg);
void		pb(t_stack **a, t_stack **b, t_config *cfg);
void		sa(t_stack **a, t_config *cfg);
void		sb(t_stack **b, t_config *cfg);
void		ss(t_stack **a, t_stack **b, t_config *cfg);
void		ra(t_stack **a, t_config *cfg);
void		rb(t_stack **b, t_config *cfg);
void		rr(t_stack **a, t_stack **b, t_config *cfg);
void		rra(t_stack **a, t_config *cfg);
void		rrb(t_stack **b, t_config *cfg);
void		rrr(t_stack **a, t_stack **b, t_config *cfg);

/* --- algo/ --- */

t_strategy	resolve_strategy(const t_config *cfg);
void		sort_stack(t_stack **a, t_stack **b, int size, t_config *cfg);
void		sort_three(t_stack **a, t_config *cfg);
void		sort_small(t_stack **a, int size, t_config *cfg);
void		selection_sort(t_stack **a, t_stack **b, int size, t_config *cfg);
void		chunk_sort(t_stack **a, t_stack **b, int size, t_config *cfg);
void		radix_sort(t_stack **a, t_stack **b, int size, t_config *cfg);

/* --- algo/turk/ --- */

void		turk_sort(t_stack **a, t_stack **b, int size, t_config *cfg);
void		push_all_but_three(t_stack **a, t_stack **b, int size,
				t_config *cfg);
void		update_positions(t_stack *s);
int			target_pos(t_stack *a, int index);
void		compute_targets(t_stack *a, t_stack *b);
int			rotation_cost(int pos, int size);
void		compute_costs(t_stack *a, t_stack *b);
t_stack		*find_cheapest(t_stack *b);
void		rotate_a(t_stack **a, int cost, t_config *cfg);
void		rotate_b(t_stack **b, int cost, t_config *cfg);
void		execute_move(t_stack **a, t_stack **b, t_stack *move,
				t_config *cfg);

/* --- bench/ --- */

void		print_benchmark(const t_config *cfg);

/* --- checker/ --- */

bool		run_instructions(t_stack **a, t_stack **b);

/* --- utils/ --- */

int			print_error(void);
void		free_split(char **s);
int			abs_value(int n);
int			sqrt_int(int n);

#endif
