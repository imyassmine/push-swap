#include "push_swap.h"

void	rra(t_stack **a, t_config *cfg)
{
	op_run(RRA, a, NULL, cfg);
}

void	rrb(t_stack **b, t_config *cfg)
{
	op_run(RRB, NULL, b, cfg);
}

void	rrr(t_stack **a, t_stack **b, t_config *cfg)
{
	op_run(RRR, a, b, cfg);
}
