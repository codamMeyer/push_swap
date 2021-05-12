#include "insertion_sort.h"
#include "sorting_utils.h"
#include <stack/processor.h>
#include <stack/stack_utils.h>
#include <stddef.h>
#include <libft.h>
#include <unistd.h>
#include <stdio.h>
#include <utils/defs.h>
#include <utils/status.h>
#include <stdlib.h>
#include <fcntl.h>

static int	push_elements_back_to_stack_a(t_stack_pair *stacks,
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

static int	move_to_stack_b_in_ascending_order(t_stack_pair *stacks,
										int num_elements,
										const int *sorted,
										t_write_instruction write_instruction)
{
	int					i;
	t_optional_index	element_index;
	int					num_moves;

	num_moves = 0;
	i = 0;
	while (i < num_elements - 2 && !is_sorted(&stacks->a, is_ascending))
	{
		element_index = find_element_index(&(stacks->a), sorted[i]);
		num_moves += move_element_to_stack_b(stacks, element_index.index, \
												write_instruction);
		++i;
	}
	return (num_moves);
}

static int	swap_bottom_elements_if_needed(t_stack_pair *stacks,
						t_write_instruction write_instruction)
{
	int	num_moves;

	num_moves = 0;
	if (stacks->a.elements[stacks->a.top] > \
			stacks->a.elements[stacks->a.top - 1])
	{
		sa(stacks);
		write_instruction(STR_SA, 1);
		++num_moves;
	}
	return (num_moves);
}

int	insertion_sort(int num_elements,
					const int *elements,
					t_write_instruction write_instruction)
{
	const int			*sorted = sort_elements(num_elements, elements);
	t_stack_pair		stacks;
	int					num_moves;

	num_moves = 0;
	stacks = create_stack_pair(num_elements);
	if (stacks.initialized && sorted != NULL)
	{
		populate_stack_a(elements, num_elements, &stacks);
		num_moves += move_to_stack_b_in_ascending_order(&stacks, num_elements, \
													 sorted, write_instruction);
		num_moves += swap_bottom_elements_if_needed(&stacks, write_instruction);
		num_moves += push_elements_back_to_stack_a(&stacks, write_instruction);
	}
	destroy_stack_pair(&stacks);
	free((void *)sorted);
	return (num_moves);
}
