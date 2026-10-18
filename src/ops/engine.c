#include "push_swap.h"

/*
** Silent primitives. They never print and never crash: on an empty stack
** (or a stack too small to change) they simply do nothing.
*/
void	op_swap(t_stack **s)
{
	t_stack	*first;

	if (!*s || !(*s)->next)
		return ;
	first = *s;
	*s = first->next;
	first->next = (*s)->next;
	(*s)->next = first;
}

void	op_push(t_stack **src, t_stack **dst)
{
	t_stack	*node;

	if (!*src)
		return ;
	node = *src;
	*src = node->next;
	node->next = *dst;
	*dst = node;
}

void	op_rotate(t_stack **s)
{
	t_stack	*first;

	if (!*s || !(*s)->next)
		return ;
	first = *s;
	*s = first->next;
	first->next = NULL;
	stack_last(*s)->next = first;
}

void	op_reverse(t_stack **s)
{
	t_stack	*before_last;
	t_stack	*last;

	if (!*s || !(*s)->next)
		return ;
	before_last = stack_before_last(*s);
	last = before_last->next;
	before_last->next = NULL;
	last->next = *s;
	*s = last;
}
