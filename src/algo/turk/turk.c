#include "push_swap.h"

/* Final step: the cyclic order of A is right, rotate the minimum on top. */
static void	align_minimum(t_stack **a, t_config *cfg)
{
	update_positions(*a);
	rotate_a(a, rotation_cost(target_pos(*a, -1), stack_size(*a)), cfg);
}

/*
** Turk algorithm (greedy, cost based). Heuristic: the number of operations
** is bounded by O(n^2) but is much lower in practice.
**   1. push all but three elements to B
**   2. sort the three remaining elements
**   3. repeat: pick the element of B that is the cheapest to insert in A
**      (rotations of A and B, merged when possible), then pa
**   4. rotate A so that the minimum is on top
*/
void	turk_sort(t_stack **a, t_stack **b, int size, t_config *cfg)
{
	if (size <= 3)
	{
		sort_small(a, size, cfg);
		return ;
	}
	push_all_but_three(a, b, size, cfg);
	sort_three(a, cfg);
	while (*b)
	{
		compute_targets(*a, *b);
		compute_costs(*a, *b);
		execute_move(a, b, find_cheapest(*b), cfg);
	}
	align_minimum(a, cfg);
}
