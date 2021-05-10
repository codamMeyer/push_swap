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
	int fd = open("num_moves", O_RDWR | O_CREAT | O_APPEND, 0777);
	ft_putstr_fd("element index ", fd);
	ft_putnbr_fd(element_index, fd);
	ft_putstr_fd(" | element ", fd);
	ft_putnbr_fd(element, fd);
	ft_putstr_fd(" | moves ", fd);
	ft_putnbr_fd(num_moves + 1, fd);
	ft_putendl_fd(" | ", fd);
	close(fd);
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
			num_moves += \
				move_element_to_stack_b(&stacks, sorted[i], write_instruction);
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

void handle_less_than_two_elements(t_stack_pair *stacks, t_write_instruction write_instruction)
{
	t_optional_int	prev_top_b;
	t_optional_int	act_top_b;

	prev_top_b = top_element(&stacks->b);
	write_instruction(STR_PB, 1);
	pb(stacks);
	act_top_b = top_element(&stacks->b);
	if (prev_top_b.initialized && (prev_top_b.element > act_top_b.element))
	{
		write_instruction(STR_SB, 1);
		sb(stacks);
	}
}

void insert_element(t_stack_pair *stacks, t_write_instruction write_instruction)
{
	const int		size_stack_b = size(&stacks->b);
	int				counter;
	t_optional_int	top_a;
	t_optional_int	top_b;
	
	counter = 0;
	top_a = top_element(&stacks->a);
	top_b = top_element(&stacks->b);
	if (!top_b.initialized || size_stack_b < 2)
	{
		handle_less_than_two_elements(stacks, write_instruction);
		return ;
	}
	if (top_a.element < stacks->b.elements[0])
	{
		write_instruction(STR_PB, 1);
		pb(stacks);
		write_instruction(STR_RB, 1);
		rb(stacks);
		return ;
	}
	while (top_b.element > top_a.element)
	{
		write_instruction(STR_RB, 1);
		rb(stacks);
		top_a = top_element(&stacks->a);
		top_b = top_element(&stacks->b);
		++counter;
	}
	write_instruction(STR_PB, 1);
	pb(stacks);
	while (counter > 0)
	{
		write_instruction(STR_RRB, 1);
		rrb(stacks);
		--counter;
	}
}