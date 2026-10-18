#include "push_swap.h"

static int	find_max_pos(t_stack *b)
{
	int	max_idx;
	int	max_pos;
	int	pos;

	max_idx = b->index;
	max_pos = 0;
	pos = 0;
	while (b)
	{
		if (b->index > max_idx)
		{
			max_idx = b->index;
			max_pos = pos;
		}
		pos++;
		b = b->next;
	}
	return (max_pos);
}

static void	bring_max_to_top(t_stack **b, t_config *cfg)
{
	int	size;
	int	pos;

	size = stack_size(*b);
	pos = find_max_pos(*b);
	if (pos <= size / 2)
	{
		while (pos-- > 0)
			rb(b, cfg);
	}
	else
	{
		while (pos++ < size)
			rrb(b, cfg);
	}
}

/* Pass 1: push by sliding windows of `chunk` ranks (small ranks sink in B). */
static void	push_chunks_to_b(t_stack **a, t_stack **b, int chunk,
				t_config *cfg)
{
	int	pushed;

	pushed = 0;
	while (*a)
	{
		if ((*a)->index <= pushed)
		{
			pb(a, b, cfg);
			if ((*b)->next)
				rb(b, cfg);
			pushed++;
		}
		else if ((*a)->index <= pushed + chunk)
		{
			pb(a, b, cfg);
			pushed++;
		}
		else
			ra(a, cfg);
	}
}

/*
** Chunk sort, O(n sqrt(n)) operations: windows of about sqrt(n) ranks go
** to B, then the maxima are brought back one by one.
*/
void	chunk_sort(t_stack **a, t_stack **b, int size, t_config *cfg)
{
	push_chunks_to_b(a, b, sqrt_int(size), cfg);
	while (*b)
	{
		bring_max_to_top(b, cfg);
		pa(a, b, cfg);
	}
}
