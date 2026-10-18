#include "push_swap.h"

void	sa(t_stack **a, t_config *cfg)
{
	op_run(SA, a, NULL, cfg);
}

void	sb(t_stack **b, t_config *cfg)
{
	op_run(SB, NULL, b, cfg);
}

void	ss(t_stack **a, t_stack **b, t_config *cfg)
{
	op_run(SS, a, b, cfg);
}
