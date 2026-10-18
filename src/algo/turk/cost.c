#include "push_swap.h"

int	rotation_cost(int pos, int size)
{
	if (pos <= size / 2)
		return (pos);
	return (pos - size);
}

void	compute_costs(t_stack *a, t_stack *b)
{
	int	size_a;
	int	size_b;

	size_a = stack_size(a);
	size_b = stack_size(b);
	while (b)
	{
		b->cost_b = rotation_cost(b->pos, size_b);
		b->cost_a = rotation_cost(b->target, size_a);
		b = b->next;
	}
}

/*
** Real cost of a move. When both rotations go the same way, rr / rrr
** perform them together, so the cost is the larger of the two, not the sum.
*/
static int	move_cost(const t_stack *node)
{
	int	ca;
	int	cb;
	int	same_dir;

	same_dir = (node->cost_a >= 0) == (node->cost_b >= 0);
	ca = abs_value(node->cost_a);
	cb = abs_value(node->cost_b);
	if (same_dir && ca > cb)
		return (ca);
	if (same_dir)
		return (cb);
	return (ca + cb);
}

t_stack	*find_cheapest(t_stack *b)
{
	t_stack	*cheapest;
	int		best;

	cheapest = b;
	best = move_cost(b);
	while (b)
	{
		if (move_cost(b) < best)
		{
			best = move_cost(b);
			cheapest = b;
		}
		b = b->next;
	}
	return (cheapest);
}
