#include "push_swap.h"

int	print_error(void)
{
	ft_putendl_fd("Error", 2);
	return (EXIT_FAILURE);
}

void	free_split(char **s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

int	abs_value(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	sqrt_int(int n)
{
	int	i;

	i = 1;
	while (i * i <= n)
		i++;
	return (i - 1);
}
