#include "push_swap.h"

/*
** Reads instructions from stdin, one per line, and applies them silently.
** Returns false on the first line that is not a valid instruction.
*/
bool	run_instructions(t_stack **a, t_stack **b)
{
	char	*line;
	int		op;

	line = get_next_line(0);
	while (line)
	{
		op = op_from_name(line);
		free(line);
		if (op < 0)
			return (false);
		op_apply(op, a, b);
		line = get_next_line(0);
	}
	return (true);
}
