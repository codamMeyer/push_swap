#include "bucket_sort_utils.h"
#include <utils/math_utils.h>

t_optional_index	search_stack_top(const t_stack *stack,
									const t_bucket *bucket)
{
	const int			s_size = size(stack);
	const int			half_stack = s_size - ft_ceil((double)s_size / 2.0);
	t_optional_index	index;

	index.initialized = FALSE;
	index.value = stack->top;
	while (index.value >= half_stack)
	{
		if (is_part_of_bucket(stack->elements[index.value], bucket))
		{
			index.initialized = TRUE;
			return (index);
		}
		--index.value;
	}
	return (index);
}

t_optional_index	search_stack_bottom(const t_stack *stack,
										const t_bucket *bucket)
{
	const int			stack_size = size(stack);
	const int			half_stack = ft_floor((double)stack_size / 2.0);
	t_optional_index	index;

	index.initialized = FALSE;
	index.value = 0;
	while (index.value < half_stack)
	{
		if (is_part_of_bucket(stack->elements[index.value], bucket))
		{
			index.initialized = TRUE;
			return (index);
		}
		++index.value;
	}
	return (index);
}

static t_index	return_closest_index(int stack_top,
								t_optional_index bottom,
								t_optional_index top)
{
	const int	num_moves_top = stack_top - top.value;
	const int	num_moves_bottom = bottom.value + 1;
	t_index		closest_index;

	if (!bottom.initialized)
		closest_index.value = top.value;
	else if (!top.initialized)
		closest_index.value = bottom.value;
	else if (num_moves_top < num_moves_bottom)
		closest_index.value = top.value;
	else
		closest_index.value = bottom.value;
	return (closest_index);
}

t_index	find_element_index_to_move(const t_stack_pair *stacks,
										const t_bucket *bucket)
{
	const t_optional_index	bottom = search_stack_bottom(&stacks->a, bucket);
	const t_optional_index	top = search_stack_top(&stacks->a, bucket);

	return (return_closest_index(stacks->a.top, bottom, top));
}

int	move_element_to_stack_a(t_stack_pair *stacks,
							t_index index,
							t_write_instruction write_instruction)
{
	const t_bool	close_to_top = is_close_to_top(&stacks->b, index);
	int				num_moves;

	num_moves = 1;
	if (index.value == (stacks->b.top - 1))
	{
		execute_operation(stacks, num_moves, sb);
		write_instruction(STR_SB, num_moves);
	}
	else if (close_to_top)
	{
		num_moves = stacks->b.top - index.value;
		execute_operation(stacks, num_moves, rb);
		write_instruction(STR_RB, num_moves);
	}
	else
	{
		num_moves = index.value + 1;
		execute_operation(stacks, num_moves, rrb);
		write_instruction(STR_RRB, num_moves);
	}
	pa(stacks);
	write_instruction(STR_PA, 1);
	return (num_moves + 1);
}
