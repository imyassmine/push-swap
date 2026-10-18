#include "push_swap.h"

static int	max_bits(int size)
{
	int	bits;

	bits = 0;
	while ((size - 1) >> bits)
		bits++;
	return (bits);
}

/*
** Binary LSD radix sort on the ranks, O(n log n) operations:
** one pass per bit, each pass costs at most 2n operations.
*/
void	radix_sort(t_stack **a, t_stack **b, int size, t_config *cfg)
{
	int	bit;
	int	i;
	int	bits;

	bits = max_bits(size);
	bit = 0;
	while (bit < bits)
	{
		i = 0;
		while (i < size)
		{
			if ((((*a)->index >> bit) & 1) == 1)
				ra(a, cfg);
			else
				pb(a, b, cfg);
			i++;
		}
		while (*b)
			pa(a, b, cfg);
		bit++;
	}
}
