#include "insertion_sort.h"
#include <stack/processor.h>
#include <stddef.h>
#include <libft.h>
#include <math.h>
#include <utils/defs.h>

int *sort_elements(int elements_size, int *elements)
{
	int	i;
	t_bool swapped;
	int	*sorted;

	sorted = malloc(sizeof(int) * elements_size);
	if (sorted == NULL)
		return (NULL);
	ft_memcpy(sorted, elements, elements_size);
	swapped = TRUE;
	while (swapped)
	{
		swapped = FALSE;
		i = 1;
		while (i < elements_size)
		{
			if (sorted[i] < sorted[i - 1])
			{
				swapped = TRUE;
				swap_elements(&sorted[i], &sorted[i - 1]);
			}
			++i;
		}
	}
	return (sorted);
}

int find_element_index(t_stack *stack, int element) 
{
	int i;

	i = 0;
	while (i <= stack->top)
	{
		if (element == stack->elements[i])
			return (i);
		++i;
	}
	return (NOT_FOUND);
}

void push_elements_back_to_stack_a(t_stack_pair *stacks, t_write_instruction write_instruction) 
{
	(void)stacks;
	(void)write_instruction;
}

void bring_element_to_top_of_a(t_stack_pair *stacks, int counter, t_operation operation)
{
	while (counter > 0)
	{
		operation(stacks);
		--counter;
	}
}

void move_element_to_stack_b(t_stack_pair *stacks, int element, t_write_instruction write_instruction)
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
}

int insertion_sort(int elements_size, int *elements, t_write_instruction write_instruction) 
{
	(void)elements_size;
	(void)elements;
	(void)write_instruction;
	//free sorted
	return (0);
}
