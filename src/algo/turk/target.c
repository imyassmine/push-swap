#include "push_swap.h"

void	update_positions(t_stack *s)
{
	int	i;

	i = 0;
	while (s)
	{
		s->pos = i++;
		s = s->next;
	}
}

/*
** Position in A where an element of rank `index` must land: right above
** the smallest rank that is greater than it, else on the minimum.
** Positions of A must be up to date (update_positions).
*/
int	target_pos(t_stack *a, int index)
{
	t_stack	*best;
	t_stack	*min;

	best = NULL;
	min = a;
	while (a)
	{
		if (a->index > index && (!best || a->index < best->index))
			best = a;
		if (a->index < min->index)
			min = a;
		a = a->next;
	}
	if (best)
		return (best->pos);
	return (min->pos);
}

void	compute_targets(t_stack *a, t_stack *b)
{
	update_positions(a);
	update_positions(b);
	while (b)
	{
		b->target = target_pos(a, b->index);
		b = b->next;
	}
}
