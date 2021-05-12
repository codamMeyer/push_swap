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

int	insertion_sort(int num_elements,
					const int *elements,
					t_write_instruction write_instruction)
{
	const int		*sorted = sort_elements(num_elements, elements);
	t_stack_pair	stacks;
	int				num_moves;
	int				i;

	num_moves = 0;
	stacks = create_stack_pair(num_elements);
	if (stacks.initialized && sorted != NULL)
	{
		populate_stack_a(elements, num_elements, &stacks);
		i = 0;
		while (i < num_elements - 2 && !is_sorted(&stacks.a, is_ascending))
		{
			num_moves += \
			move_element_to_stack_b(&stacks, sorted[i], write_instruction);
			++i;
		}
		if (stacks.a.elements[stacks.a.top] > \
			stacks.a.elements[stacks.a.top - 1])
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
