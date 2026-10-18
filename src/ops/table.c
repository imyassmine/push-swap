#include "push_swap.h"

typedef struct s_op_def
{
	char	*name;
	void	(*func)(t_stack **);
	bool	on_a;
	bool	on_b;
}	t_op_def;

/* One table, two users: push_swap prints the name, checker parses it. */
static const t_op_def	g_ops[OP_COUNT] = {
{"sa", op_swap, true, false},
{"sb", op_swap, false, true},
{"ss", op_swap, true, true},
{"pa", NULL, false, false},
{"pb", NULL, false, false},
{"ra", op_rotate, true, false},
{"rb", op_rotate, false, true},
{"rr", op_rotate, true, true},
{"rra", op_reverse, true, false},
{"rrb", op_reverse, false, true},
{"rrr", op_reverse, true, true},
};

void	op_apply(t_op op, t_stack **a, t_stack **b)
{
	if (op == PA)
		op_push(b, a);
	else if (op == PB)
		op_push(a, b);
	else
	{
		if (g_ops[op].on_a)
			g_ops[op].func(a);
		if (g_ops[op].on_b)
			g_ops[op].func(b);
	}
}

/* "rra\n" -> RRA. Returns -1 for anything that is not an instruction. */
int	op_from_name(const char *line)
{
	size_t	len;
	int		op;

	op = 0;
	while (op < OP_COUNT)
	{
		len = ft_strlen(g_ops[op].name);
		if (!ft_strncmp(line, g_ops[op].name, len)
			&& (line[len] == '\n' || line[len] == '\0'))
			return (op);
		op++;
	}
	return (-1);
}

char	*op_name(t_op op)
{
	return (g_ops[op].name);
}
