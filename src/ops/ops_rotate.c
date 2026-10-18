#include "push_swap.h"

void	ra(t_stack **a, t_config *cfg)
{
	op_run(RA, a, NULL, cfg);
}

void	rb(t_stack **b, t_config *cfg)
{
	op_run(RB, NULL, b, cfg);
}

void	rr(t_stack **a, t_stack **b, t_config *cfg)
{
	op_run(RR, a, b, cfg);
}
