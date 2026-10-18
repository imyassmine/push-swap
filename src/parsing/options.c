#include "push_swap.h"

static bool	is_opt(const char *arg, const char *name)
{
	return (!ft_strncmp(arg, name, ft_strlen(name) + 1));
}

static bool	set_strategy(const char *arg, t_config *cfg)
{
	if (is_opt(arg, "--simple"))
		cfg->strategy = SIMPLE;
	else if (is_opt(arg, "--medium"))
		cfg->strategy = MEDIUM;
	else if (is_opt(arg, "--complex"))
		cfg->strategy = COMPLEX;
	else if (is_opt(arg, "--turk"))
		cfg->strategy = TURK;
	else if (is_opt(arg, "--adaptive"))
		cfg->strategy = ADAPTIVE;
	else
		return (false);
	return (true);
}

/*
** Reads the leading "--option" arguments (any order, at most one strategy).
** On success, *first is the index of the first number argument.
*/
bool	parse_options(int argc, char **argv, t_config *cfg, int *first)
{
	int	nb_strategy;

	cfg->strategy = ADAPTIVE;
	cfg->bench_mode = false;
	nb_strategy = 0;
	*first = 1;
	while (*first < argc && !ft_strncmp(argv[*first], "--", 2))
	{
		if (is_opt(argv[*first], "--bench"))
			cfg->bench_mode = true;
		else if (set_strategy(argv[*first], cfg))
			nb_strategy++;
		else
			return (false);
		(*first)++;
	}
	return (nb_strategy <= 1);
}
