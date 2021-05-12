#include "bucket_sort.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <stack/processor.h>

t_optional_index	search_stack_top(const t_stack *stack,
									const t_bucket *bucket)
{
	const int			s_size = size(stack);
	const int			half_stack = s_size - ceil((double)s_size / 2.0);
	t_optional_index	element_index;
	int					i;

	element_index.initialized = FALSE;
	i = stack->top;
	while (i >= half_stack)
	{
		if (is_part_of_bucket(stack->elements[i], bucket))
		{
			element_index.index = i;
			element_index.initialized = TRUE;
			return (element_index);
		}
		--i;
	}
	return (element_index);
}

t_optional_index	search_stack_bottom(const t_stack *stack,
										const t_bucket *bucket)
{
	const int			stack_size = size(stack);
	const int			half_stack = floor((double)stack_size / 2.0);
	t_optional_index	element_index;
	int					i;

	element_index.initialized = FALSE;
	i = 0;
	while (i < half_stack)
	{
		if (is_part_of_bucket(stack->elements[i], bucket))
		{
			element_index.index = i;
			element_index.initialized = TRUE;
			return (element_index);
		}
		++i;
	}
	return (element_index);
}

static int	return_closest_index(int stack_top,
								int bottom_index,
								int top_index)
{
	const int	num_moves_top = stack_top - top_index;
	const int	num_moves_bottom = bottom_index + 1;

	if (num_moves_top < num_moves_bottom)
		return (top_index);
	return (bottom_index);
}

static int	find_element_index_to_move(const t_stack_pair *stacks,
										const t_bucket *bucket)
{
	const t_optional_index	bottom = search_stack_bottom(&stacks->a, bucket);
	const t_optional_index	top = search_stack_top(&stacks->a, bucket);
 
	if (!bottom.initialized)
		return (top.index);
	else if (!top.initialized)
		return (bottom.index);

	return (return_closest_index(stacks->a.top, bottom.index, top.index));
}

static int	move_element_to_stack_a(t_stack_pair *stacks,
							int element,
							t_write_instruction write_instruction)
{
	const t_optional_index	element_index = \
								find_element_index(&(stacks->b), element);
	const int				num_moves = stacks->b.top - element_index.index;

	execute_operation(stacks, num_moves, rb);
	write_instruction(STR_RB, num_moves);
	pa(stacks);
	write_instruction(STR_PA, 1);
	execute_operation(stacks, num_moves, rrb);
	write_instruction(STR_RRB, num_moves);
	return ((num_moves * 2) + 1);
}

// receive bucket from outside
int	bucket_sort(int elements_size,
				const int *elements,
				t_write_instruction write_instruction)
{
	const int		*sorted = sort_elements(elements_size, elements);
	const int		bucket_size = 25;
	int				element_index;
	t_bucket		bucket;
	t_stack_pair	stacks;
	int				num_moves;

	num_moves = 0;
	stacks = create_stack_pair(elements_size);
	if (stacks.initialized && sorted != NULL)
	{
		bucket = create_bucket(bucket_size, sorted);
		populate_stack_a(elements, elements_size, &stacks);
		while (bucket.is_valid)
		{
			while (bucket.missing_elements)
			{
				element_index = find_element_index_to_move(&stacks, &bucket);
				num_moves += \
				move_element_to_stack_b(&stacks, element_index, write_instruction);
				--bucket.missing_elements;
			}
			bucket = get_next_bucket(bucket, bucket_size, sorted, elements_size);
		}
	}
	int i = elements_size - 1;
	while (i >= 0)
	{
		num_moves += \
			move_element_to_stack_a(&stacks, sorted[i], write_instruction);
		--i;
	}
	free((void *)sorted);
	destroy_stack_pair(&stacks);
	return (num_moves);
}
