#include "push_swap.h"

static char	*strategy_name(t_strategy s)
{
	if (s == SIMPLE)
		return ("Simple");
	if (s == MEDIUM)
		return ("Medium");
	if (s == COMPLEX)
		return ("Complex");
	if (s == TURK)
		return ("Turk");
	return ("Adaptive");
}

static char	*complexity(t_strategy s)
{
	if (s == SIMPLE)
		return ("O(n²)");
	if (s == MEDIUM)
		return ("O(n√n)");
	if (s == COMPLEX)
		return ("O(nlogn)");
	return ("greedy heuristic");
}

static void	print_ops(const t_stats *stats, t_op from, t_op to)
{
	ft_dprintf(2, "[bench]");
	while (from <= to)
	{
		ft_dprintf(2, " %s: %d", op_name(from), stats->count[from]);
		from++;
	}
	ft_dprintf(2, "\n");
}

/*
** Report on stderr, so that stdout only carries the instructions and
** `push_swap --bench ... | checker ...` keeps working.
*/
void	print_benchmark(const t_config *cfg)
{
	int	hundredths;

	hundredths = (int)(cfg->disorder * 10000 + 0.5);
	ft_dprintf(2, "[bench] disorder: %d.%d%d%%\n",
		hundredths / 100, hundredths % 100 / 10, hundredths % 10);
	if (cfg->strategy == ADAPTIVE)
		ft_dprintf(2, "[bench] strategy: Adaptive / %s\n",
			complexity(resolve_strategy(cfg)));
	else
		ft_dprintf(2, "[bench] strategy: %s / %s\n",
			strategy_name(cfg->strategy), complexity(cfg->strategy));
	ft_dprintf(2, "[bench] total_ops: %d\n", cfg->stats.total);
	print_ops(&cfg->stats, SA, PB);
	print_ops(&cfg->stats, RA, RRR);
}
