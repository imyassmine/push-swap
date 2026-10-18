#include "push_swap.h"

void	pa(t_stack **a, t_stack **b, t_config *cfg)
{
	op_run(PA, a, b, cfg);
}

void	pb(t_stack **a, t_stack **b, t_config *cfg)
{
	op_run(PB, a, b, cfg);
}
