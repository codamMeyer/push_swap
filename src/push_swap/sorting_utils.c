#include "sorting_utils.h"
#include <utils/math_utils.h>

t_bool	is_close_to_top(const t_stack *stack, t_index index)
{
	const int		stack_size = size(stack);
	const int		middle_of_stack = ft_floor((double)stack_size / 2.0);

	return (index.value >= middle_of_stack);
}

void	execute_operation(t_stack_pair *stacks,
							int counter,
							t_operation operation)
{
	while (counter > 0)
	{
		operation(stacks);
		--counter;
	}
}

int	move_element_to_stack_b(t_stack_pair *stacks,
							t_index index,
							t_write_instruction write_instruction)
{
	const t_bool	close_to_top = is_close_to_top(&stacks->a, index);
	int				num_moves;

	if (close_to_top)
	{
		num_moves = stacks->a.top - index.value;
		execute_operation(stacks, num_moves, ra);
		write_instruction(STR_RA, num_moves);
	}
	else
	{
		num_moves = index.value + 1;
		execute_operation(stacks, num_moves, rra);
		write_instruction(STR_RRA, num_moves);
	}
	pb(stacks);
	write_instruction(STR_PB, 1);
	return (num_moves + 1);
}

t_optional_index	find_element_index(t_stack *stack, int element)
{
	t_optional_index	index;

	index.value = 0;
	index.initialized = TRUE;
	while (index.value <= stack->top)
	{
		if (element == stack->elements[index.value])
			return (index);
		++index.value;
	}
	index.initialized = FALSE;
	index.value = -1;
	return (index);
}
