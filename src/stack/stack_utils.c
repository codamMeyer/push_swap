#include "stack_utils.h"

t_bool	is_ascending(int top, int bottom)
{
	return (top < bottom);
}

t_bool	is_sorted(const t_stack *stack, t_compare compare)
{
	const int	stack_size = size(stack);
	int			i;

	i = 1;
	while (i < stack_size)
	{
		if (!compare(stack->elements[i], stack->elements[i - 1]))
		{
			return (FALSE);
		}
		++i;
	}
	return (TRUE);
}
