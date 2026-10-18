#include "push_swap.h"

/* Strict int parser: overflow is checked at every digit. */
static bool	parse_int(const char *s, int *out)
{
	long	n;
	int		sign;

	sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	if (!ft_isdigit(*s))
		return (false);
	n = 0;
	while (ft_isdigit(*s))
	{
		n = n * 10 + (*s++ - '0');
		if (n * sign > INT_MAX || n * sign < INT_MIN)
			return (false);
	}
	if (*s)
		return (false);
	*out = (int)(n * sign);
	return (true);
}

static bool	has_duplicate(const int *v, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = i + 1;
		while (j < n)
		{
			if (v[i] == v[j])
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

static bool	fill_values(char **tokens, t_input *in)
{
	int	i;

	while (tokens[in->count])
		in->count++;
	if (in->count == 0)
		return (false);
	in->values = malloc(sizeof(int) * in->count);
	if (!in->values)
		return (false);
	i = 0;
	while (i < in->count)
	{
		if (!parse_int(tokens[i], &in->values[i]))
			break ;
		i++;
	}
	if (i == in->count && !has_duplicate(in->values, in->count))
		return (true);
	free(in->values);
	in->values = NULL;
	return (false);
}

/*
** Accepts either several arguments ("3 1 2") or a single quoted,
** space-separated one ("3 1 2"). Shared by push_swap and checker.
*/
bool	parse_numbers(int argc, char **argv, int first, t_input *in)
{
	char	**tokens;
	bool	split;
	bool	ok;

	in->values = NULL;
	in->count = 0;
	if (first >= argc)
		return (false);
	split = (argc - first == 1);
	tokens = argv + first;
	if (split)
		tokens = ft_split(argv[first], ' ');
	if (!tokens)
		return (false);
	ok = fill_values(tokens, in);
	if (split)
		free_split(tokens);
	return (ok);
}
