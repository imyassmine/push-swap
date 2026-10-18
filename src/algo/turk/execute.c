#include "push_swap.h"

void	rotate_a(t_stack **a, int cost, t_config *cfg)
{
	while (cost > 0)
	{
		ra(a, cfg);
		cost--;
	}
	while (cost < 0)
	{
		rra(a, cfg);
		cost++;
	}
}

void	rotate_b(t_stack **b, int cost, t_config *cfg)
{
	while (cost > 0)
	{
		rb(b, cfg);
		cost--;
	}
	while (cost < 0)
	{
		rrb(b, cfg);
		cost++;
	}
}

/* Rotations in the same direction are merged into rr / rrr. */
static void	rotate_both(t_stack **a, t_stack **b, t_stack *m, t_config *cfg)
{
	while (m->cost_a > 0 && m->cost_b > 0)
	{
		rr(a, b, cfg);
		m->cost_a--;
		m->cost_b--;
	}
	while (m->cost_a < 0 && m->cost_b < 0)
	{
		rrr(a, b, cfg);
		m->cost_a++;
		m->cost_b++;
	}
}

void	execute_move(t_stack **a, t_stack **b, t_stack *move, t_config *cfg)
{
	rotate_both(a, b, move, cfg);
	rotate_a(a, move->cost_a, cfg);
	rotate_b(b, move->cost_b, cfg);
	pa(a, b, cfg);
}
