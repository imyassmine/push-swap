#include "push_swap.h"

void	free_stack(t_stack *stack)
{
	t_stack	*next;

	while (stack)
	{
		next = stack->next;
		free(stack);
		stack = next;
	}
}

t_stack	*stack_from_input(const t_input *in)
{
	t_stack	*stack;
	t_stack	*node;
	int		i;

	stack = NULL;
	i = 0;
	while (i < in->count)
	{
		node = stack_new(in->values[i]);
		if (!node)
		{
			free_stack(stack);
			return (NULL);
		}
		stack_add_back(&stack, node);
		i++;
	}
	return (stack);
}

/* index = rank of the value in the sorted order, from 0 to n - 1 */
void	index_stack(t_stack *a)
{
	t_stack	*cur;
	t_stack	*other;

	cur = a;
	while (cur)
	{
		cur->index = 0;
		other = a;
		while (other)
		{
			if (other->value < cur->value)
				cur->index++;
			other = other->next;
		}
		cur = cur->next;
	}
}

bool	is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (false);
		stack = stack->next;
	}
	return (true);
}

/* Fraction of out-of-order pairs: 0.0 (sorted) to 1.0 (reversed). */
double	compute_disorder(t_stack *stack)
{
	t_stack	*i;
	t_stack	*j;
	long	mistakes;
	long	pairs;

	mistakes = 0;
	pairs = 0;
	i = stack;
	while (i)
	{
		j = i->next;
		while (j)
		{
			pairs++;
			if (i->value > j->value)
				mistakes++;
			j = j->next;
		}
		i = i->next;
	}
	if (!pairs)
		return (0.0);
	return ((double)mistakes / (double)pairs);
}
