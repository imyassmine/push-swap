#include "push_swap.h"

static int	find_min_pos(t_stack *a)
{
	int	min_idx;
	int	min_pos;
	int	pos;

	min_idx = a->index;
	min_pos = 0;
	pos = 0;
	while (a)
	{
		if (a->index < min_idx)
		{
			min_idx = a->index;
			min_pos = pos;
		}
		pos++;
		a = a->next;
	}
	return (min_pos);
}

static void	bring_to_top(t_stack **a, int pos, int size, t_config *cfg)
{
	if (pos <= size / 2)
	{
		while (pos-- > 0)
			ra(a, cfg);
	}
	else
	{
		while (pos++ < size)
			rra(a, cfg);
	}
}

/*
** Selection sort, O(n^2) operations: push the minimum to B until three
** elements remain, sort those, then bring everything back with pa.
*/
void	selection_sort(t_stack **a, t_stack **b, int size, t_config *cfg)
{
	while (size > 3)
	{
		bring_to_top(a, find_min_pos(*a), size, cfg);
		pb(a, b, cfg);
		size--;
	}
	sort_small(a, size, cfg);
	while (*b)
		pa(a, b, cfg);
}
