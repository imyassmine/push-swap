#include "push_swap.h"

t_stack	*stack_new(int value)
{
	t_stack	*node;

	node = malloc(sizeof(t_stack));
	if (!node)
		return (NULL);
	node->value = value;
	node->index = -1;
	node->pos = 0;
	node->target = 0;
	node->cost_a = 0;
	node->cost_b = 0;
	node->next = NULL;
	return (node);
}

void	stack_add_back(t_stack **lst, t_stack *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
		stack_last(*lst)->next = new;
}

int	stack_size(t_stack *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

t_stack	*stack_last(t_stack *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_stack	*stack_before_last(t_stack *lst)
{
	while (lst && lst->next && lst->next->next)
		lst = lst->next;
	return (lst);
}
