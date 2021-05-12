#include "bucket_sort.h"
#include <stdlib.h>
#include <stdio.h>
#include <stack/processor.h>
#include <stack/stack_utils.h>
#include <utils/math_utils.h>
#include <libft.h>
#include <fcntl.h>


t_optional_index	search_stack_top(const t_stack *stack,
									const t_bucket *bucket)
{
	const int			s_size = size(stack);
	const int			half_stack = s_size - ft_ceil((double)s_size / 2.0);
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
	const int			half_stack = ft_floor((double)stack_size / 2.0);
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


static t_bool	is_close_to_top_b(const t_stack_pair *stacks, int element_index)
{
	const int		stack_size = size(&stacks->b);
	const int		middle_of_stack = ft_floor((double)stack_size / 2.0);

	return (element_index >= middle_of_stack);
}

static int	move_element_to_stack_a(t_stack_pair *stacks,
							int element_index,
							t_write_instruction write_instruction)
{
	const t_bool	close_to_top = is_close_to_top_b(stacks, element_index);
	int				num_moves;

	if (element_index == -1)
		return (0);
	if (close_to_top)
	{
		num_moves = stacks->b.top - element_index;
		execute_operation(stacks, num_moves, rb);
		write_instruction(STR_RB, num_moves);
	}
	else
	{
		num_moves = element_index + 1;
		execute_operation(stacks, num_moves, rrb);
		write_instruction(STR_RRB, num_moves);
	}
	pa(stacks);
	write_instruction(STR_PA, 1);
	return (num_moves + 1);
}

int	get_elements_from_bucket(t_stack_pair *stacks,
							t_bucket *bucket,
							t_write_instruction write_instruction)
{
	int	element_index;
	int	num_moves;

	num_moves = 0;
	while (bucket->missing_elements)
	{
		element_index = find_element_index_to_move(stacks, bucket);
		num_moves += \
		move_element_to_stack_b(stacks, element_index, write_instruction);
		--bucket->missing_elements;
	}
	return (num_moves);
}

int	move_all_elements_back_to_a(t_stack_pair *stacks,
								int num_elements,
								const int *sorted,
								t_write_instruction write_instruction)
{
	int	i;
	int	num_moves;
	t_optional_index element_index;

	i = num_elements - 1;
	num_moves = 0;
	while (i >= 0)
	{
		element_index = find_element_index(&(stacks->b), sorted[i]);
		num_moves += \
			move_element_to_stack_a(stacks, element_index.index, write_instruction);
		--i;
	}
	return (num_moves);
}

int	bucket_sort(int num_elements,
				const int *elements,
				int bucket_size,
				t_write_instruction write_instruction)
{
	const int		*sorted = sort_elements(num_elements, elements);
	t_bucket		bucket;
	t_stack_pair	stacks;
	int				num_moves;

	num_moves = 0;
	stacks = create_stack_pair(num_elements);
	if (stacks.initialized && sorted != NULL)
	{
		bucket = create_bucket(bucket_size, sorted);
		populate_stack_a(elements, num_elements, &stacks);
		while (bucket.is_valid)
		{
			num_moves += \
				get_elements_from_bucket(&stacks, &bucket, write_instruction);
			bucket = get_next_bucket(bucket, bucket_size, sorted, num_elements);
		}
	}
	num_moves += move_all_elements_back_to_a(&stacks, num_elements, \
											sorted, write_instruction);
	free((void *)sorted);
	destroy_stack_pair(&stacks);
	return (num_moves);
}

static int	select_best_bucket_size(const int *sizes, int num_buckets, int results[])
{
	int	i;
	int	index_min_value;

	i = 1;
	index_min_value = 0;
	while (i < num_buckets)
	{
		if (results[i] < results[index_min_value])
			index_min_value = i;
		++i;
	}
	return (sizes[index_min_value]);
}

int	try_many_buckets(int num_elements,
					const int *elements,
					t_write_instruction write_instruction)
{
	const int	num_buckets = 10;
	const int	sizes[10] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};
	int			results[10];
	int			i;
	i = 0;
	while (i < num_buckets && sizes[i] < num_elements)
	{
		results[i] = bucket_sort(num_elements, elements, sizes[i], write_instruction);
		++i;
	}
	const int	fd = open("buckets", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	i = 0;
	while (i < num_buckets)
	{
		ft_putnbr_fd(sizes[i], fd);
		ft_putstr_fd(" ", fd);
		ft_putnbr_fd(results[i], fd);
		ft_putendl_fd(" ", fd);
		++i;
	}
	close(fd);
	return (select_best_bucket_size(sizes, num_buckets, results));
}

