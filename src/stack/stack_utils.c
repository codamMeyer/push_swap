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

t_status	is_stack_sorted(const t_stack *stack_a, int initial_size)
{
	const int	stack_size = size(stack_a);

	if (stack_size != initial_size || !is_sorted(stack_a, is_ascending))
		return (KO);
	return (OK);
}
