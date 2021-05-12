#include "insertion_sort.h"
#include <stack/utils.h>
#include <stack/processor.h>
#include <stddef.h>
#include <libft.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <utils/defs.h>
#include <utils/status.h>
#include <stdlib.h>
#include <fcntl.h>

static t_status	is_stack_sorted(const t_stack *stack_a, int initial_size)
{
	const int	stack_size = size(stack_a);
	int			i;

	i = 1;
	if (stack_size != initial_size)
		return (KO);
	while (i < stack_size)
	{
		if (stack_a->elements[i] > stack_a->elements[i - 1])
		{
			return (KO);
		}
		++i;
	}
	return (OK);
}

int	find_element_index(t_stack *stack, int element)
{
	int	i;

	i = 0;
	while (i <= stack->top)
	{
		if (element == stack->elements[i])
			return (i);
		++i;
	}
	return (NOT_FOUND);
}

int	push_elements_back_to_stack_a(t_stack_pair *stacks,
									t_write_instruction write_instruction)
{
	int	num_moves;

	num_moves = 0;
	while (stacks->b.top >= 0)
	{
		pa(stacks);
		write_instruction(STR_PA, 1);
		++num_moves;
	}
	return (num_moves);
}

void	bring_element_to_top_of_a(t_stack_pair *stacks,
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
							int element,
							t_write_instruction write_instruction)
{
	const int		element_index = find_element_index(&(stacks->a), element);
	const int		stack_size = size(&stacks->a);
	const int		middle_of_stack = floor((double)stack_size / 2.0);
	const t_bool	close_to_top = (element_index >= middle_of_stack);
	int				num_moves;

	if (close_to_top)
	{
		num_moves = stacks->a.top - element_index;
		bring_element_to_top_of_a(stacks, num_moves, ra);
		write_instruction(STR_RA, num_moves);
	}
	else
	{
		num_moves = element_index + 1;
		bring_element_to_top_of_a(stacks, num_moves, rra);
		write_instruction(STR_RRA, num_moves);
	}
	pb(stacks);
	write_instruction(STR_PB, 1);
	return (num_moves + 1);
}

int	insertion_sort(int elements_size,
					int *elements,
					t_write_instruction write_instruction)
{
	const int		*sorted = sort_elements(elements_size, elements);
	t_stack_pair	stacks;
	int				num_moves;
	int				i;

	num_moves = 0;
	stacks = create_stack_pair(elements_size);
	if (stacks.initialized && sorted != NULL)
	{
		populate_stack_a(elements, elements_size, &stacks);
		i = 0;
		while (i < elements_size - 2 && is_stack_sorted(&stacks.a, elements_size) != OK)
		{
			num_moves += move_element_to_stack_b(&stacks, sorted[i], write_instruction);
			++i;
		}
		if (stacks.a.elements[stacks.a.top] > stacks.a.elements[stacks.a.top - 1])
		{
			sa(&stacks);
			write_instruction(STR_SA, 1);
			++num_moves;
		}
		num_moves += push_elements_back_to_stack_a(&stacks, write_instruction);
	}
	destroy_stack_pair(&stacks);
	free((void *)sorted);
	return (num_moves);
}