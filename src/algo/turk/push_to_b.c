#include "push_swap.h"

/*
** Phase 1: push everything but three elements to B. Elements from the lower
** half of the ranks are rotated to the bottom of B, so B ends up roughly
** ordered (big on top, small below), which makes insertions cheaper.
*/
void	push_all_but_three(t_stack **a, t_stack **b, int size, t_config *cfg)
{
	int	to_push;

	to_push = size - 3;
	while (to_push-- > 0)
	{
		pb(a, b, cfg);
		if ((*b)->next && (*b)->index < size / 2)
			rb(b, cfg);
	}
}
