#include "push_swap.h"

static int	run(t_config *cfg, t_input *in)
{
	t_stack	*a;
	t_stack	*b;

	a = stack_from_input(in);
	free(in->values);
	if (!a)
		return (print_error());
	b = NULL;
	index_stack(a);
	cfg->disorder = compute_disorder(a);
	sort_stack(&a, &b, stack_size(a), cfg);
	if (cfg->bench_mode)
		print_benchmark(cfg);
	free_stack(a);
	free_stack(b);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_config	cfg;
	t_input		in;
	int			first;

	if (argc < 2)
		return (EXIT_SUCCESS);
	ft_bzero(&cfg, sizeof(cfg));
	if (!parse_options(argc, argv, &cfg, &first)
		|| !parse_numbers(argc, argv, first, &in))
		return (print_error());
	return (run(&cfg, &in));
}
