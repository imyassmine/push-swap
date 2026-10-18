#include "push_swap.h"

/* Sorts exactly three elements in at most two operations. */
void	sort_three(t_stack **a, t_config *cfg)
{
	t_stack	*x;
	t_stack	*y;
	t_stack	*z;

	x = *a;
	y = x->next;
	z = y->next;
	if (x->index > y->index && y->index > z->index)
	{
		sa(a, cfg);
		rra(a, cfg);
	}
	else if (x->index > y->index && x->index > z->index)
		ra(a, cfg);
	else if (x->index > y->index)
		sa(a, cfg);
	else if (x->index > z->index)
		rra(a, cfg);
	else if (y->index > z->index)
	{
		sa(a, cfg);
		ra(a, cfg);
	}
}

void	sort_small(t_stack **a, int size, t_config *cfg)
{
	if (size == 2 && (*a)->index > (*a)->next->index)
		sa(a, cfg);
	else if (size == 3)
		sort_three(a, cfg);
}
