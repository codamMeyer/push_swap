#include "sorting_utils.h"
#include <utils/math_utils.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>
static t_bool	is_close_to_top(const t_stack_pair *stacks, int element_index)
{
	const int		stack_size = size(&stacks->a);
	const int		middle_of_stack = floor((double)stack_size / 2.0);

	return (element_index >= middle_of_stack);
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
							int element_index,
							t_write_instruction write_instruction)
{
	const t_bool	close_to_top = \
							is_close_to_top(stacks, element_index);
	int				num_moves;

	if (element_index == -1)
		return (0);
	if (close_to_top)
	{
		num_moves = stacks->a.top - element_index;
		execute_operation(stacks, num_moves, ra);
		write_instruction(STR_RA, num_moves);
	}
	else
	{
		num_moves = element_index + 1;
		execute_operation(stacks, num_moves, rra);
		write_instruction(STR_RRA, num_moves);
	}
	pb(stacks);
	write_instruction(STR_PB, 1);
	return (num_moves + 1);
}

t_optional_index	find_element_index(t_stack *stack, int element)
{
	t_optional_index	element_index;

	element_index.index = 0;
	element_index.initialized = TRUE;
	while (element_index.index <= stack->top)
	{
		if (element == stack->elements[element_index.index])
			return (element_index);
		++element_index.index;
	}
	element_index.initialized = FALSE;
	element_index.index = -1;
	return (element_index);
}
