#include "push_swap.h"

/* Apply an operation, print it on stdout and record it in the statistics. */
void	op_run(t_op op, t_stack **a, t_stack **b, t_config *cfg)
{
	op_apply(op, a, b);
	ft_putendl_fd(op_name(op), 1);
	cfg->stats.count[op]++;
	cfg->stats.total++;
}
