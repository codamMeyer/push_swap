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


int handle_less_than_two_elements(t_stack_pair *stacks, t_write_instruction write_instruction)
{
	t_optional_int	prev_top_b;
	t_optional_int	act_top_b;
	int				num_moves;

	num_moves = 0;
	prev_top_b = top_element(&stacks->b);
	write_instruction(STR_PB, 1);
	pb(stacks);
	++num_moves;
	act_top_b = top_element(&stacks->b);
	if (prev_top_b.initialized && (prev_top_b.element > act_top_b.element))
	{
		write_instruction(STR_SB, 1);
		sb(stacks);
		++num_moves;
	}
	return (num_moves);
}

int insert_element_at_stack_bottom(t_stack_pair *stacks, t_write_instruction write_instruction)
{
	write_instruction(STR_PB, 1);
	pb(stacks);
	write_instruction(STR_RB, 1);
	rb(stacks);
	return (2);
}

int find_element_position_in_stack_b(t_stack_pair *stacks, t_write_instruction write_instruction)
{
	t_optional_int	top_a;
	t_optional_int	top_b;
	int				counter;
	int				num_moves;

	top_a = top_element(&stacks->a);
	top_b = top_element(&stacks->b);
	counter = 0;
	num_moves = 0;
	while (top_b.element > top_a.element)
	{
		write_instruction(STR_RB, 1);
		rb(stacks);
		++num_moves;
		top_a = top_element(&stacks->a);
		top_b = top_element(&stacks->b);
		++counter;
	}
	write_instruction(STR_PB, 1);
	pb(stacks);
	++num_moves;
	while (counter > 0)
	{
		write_instruction(STR_RRB, 1);
		rrb(stacks);
		--counter;
		++num_moves;
	}
	return (num_moves);
}

int insert_element(t_stack_pair *stacks, t_write_instruction write_instruction)
{
	const int		size_stack_b = size(&stacks->b);
	int				num_moves;
	t_optional_int	top_a;
	t_optional_int	top_b;
	
	num_moves = 0;
	top_a = top_element(&stacks->a);
	top_b = top_element(&stacks->b);
	if (!top_b.initialized || size_stack_b < 2)
	{
		num_moves += handle_less_than_two_elements(stacks, write_instruction);
		return (num_moves);
	}
	if (top_a.element < stacks->b.elements[0])
	{
		num_moves += insert_element_at_stack_bottom(stacks, write_instruction);
		return (num_moves);
	}
	num_moves += find_element_position_in_stack_b(stacks, write_instruction);
	return (num_moves);
}

int	get_median(int size)
{
	return (ceil((double)size / 2.0));
}

int	insertion_sort(int elements_size,
					int *elements,
					t_write_instruction write_instruction)
{
	const int		*sorted = sort_elements(elements_size, elements);
	const int		median = get_median(elements_size);
	t_stack_pair	stacks;
	int				num_moves;
	int				i;
	int				max_elements_stack_b;

	max_elements_stack_b = elements_size - median;
	num_moves = 0;
	stacks = create_stack_pair(elements_size);
	if (stacks.initialized && sorted != NULL)
	{
		populate_stack_a(elements, elements_size, &stacks);
		i = 0;
		while (i < max_elements_stack_b && is_stack_sorted(&stacks.a, elements_size) != OK)
		{
			if (top_element(&stacks.a).element < sorted[median])
			{
				num_moves += insert_element(&stacks, write_instruction);
				++i;
			}
			else
			{
				ra(&stacks);
				write_instruction(STR_RA, 1);
				++num_moves;
			}
		}
		while (size(&stacks.a) >= 2 && is_stack_sorted(&stacks.a, elements_size) != OK)
		{
			if (stacks.a.elements[stacks.a.top] > stacks.a.elements[stacks.a.top - 1])
			{
				sa(&stacks);
				write_instruction(STR_SA, 1);
				++num_moves;
			}
			num_moves += insert_element(&stacks, write_instruction);
		}
		num_moves += push_elements_back_to_stack_a(&stacks, write_instruction);
	}
	destroy_stack_pair(&stacks);
	free((void *)sorted);
	return (num_moves);
}

// int	insertion_sort(int elements_size,
// 					int *elements,
// 					t_write_instruction write_instruction)
// {
// 	const int		*sorted = sort_elements(elements_size, elements);
// 	t_stack_pair	stacks;
// 	int				num_moves;
// 	int				i;

// 	num_moves = 0;
// 	stacks = create_stack_pair(elements_size);
// 	if (stacks.initialized && sorted != NULL)
// 	{
// 		populate_stack_a(elements, elements_size, &stacks);
// 		i = 0;
// 		while (i < elements_size - 2 && is_stack_sorted(&stacks.a, elements_size) != OK)
// 		{
// 			num_moves += 
// 				move_element_to_stack_b(&stacks, sorted[i], write_instruction);
// 			++i;
// 		}
// 		if (stacks.a.elements[stacks.a.top] > stacks.a.elements[stacks.a.top - 1])
// 		{
// 			sa(&stacks);
// 			write_instruction(STR_SA, 1);
// 			++num_moves;
// 		}
// 		num_moves += push_elements_back_to_stack_a(&stacks, write_instruction);
// 	}
// 	destroy_stack_pair(&stacks);
// 	free((void *)sorted);
// 	return (num_moves);
// }





