#include "push_swap.h"

/*
** Resolves ADAPTIVE into a concrete strategy from the measured disorder.
** This is the only place where the 0.2 / 0.5 thresholds exist.
*/
t_strategy	resolve_strategy(const t_config *cfg)
{
	if (cfg->strategy != ADAPTIVE)
		return (cfg->strategy);
	if (cfg->disorder < 0.2)
		return (SIMPLE);
	if (cfg->disorder < 0.5)
		return (MEDIUM);
	return (COMPLEX);
}

/* Entry point of the sorting phase. Indexed by SIMPLE, MEDIUM, COMPLEX, TURK */
void	sort_stack(t_stack **a, t_stack **b, int size, t_config *cfg)
{
	static const t_sort_fn	sorts[] = {
		selection_sort, chunk_sort, radix_sort, turk_sort};

	if (size < 2 || is_sorted(*a))
		return ;
	if (size <= 3)
		sort_small(a, size, cfg);
	else
		sorts[resolve_strategy(cfg)](a, b, size, cfg);
}
