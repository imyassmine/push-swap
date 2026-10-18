#include "push_swap.h"

static int	verdict(t_stack *a, t_stack *b, bool valid)
{
	if (!valid)
		return (print_error());
	if (is_sorted(a) && !b)
		ft_putendl_fd("OK", 1);
	else
		ft_putendl_fd("KO", 1);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_input	in;
	t_stack	*a;
	t_stack	*b;
	bool	valid;
	int		ret;

	if (argc < 2)
		return (EXIT_SUCCESS);
	if (!parse_numbers(argc, argv, 1, &in))
		return (print_error());
	a = stack_from_input(&in);
	free(in.values);
	if (!a)
		return (print_error());
	b = NULL;
	valid = run_instructions(&a, &b);
	ret = verdict(a, b, valid);
	free_stack(a);
	free_stack(b);
	return (ret);
}
