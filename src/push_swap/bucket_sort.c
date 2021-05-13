#include "bucket_sort.h"
#include "bucket_sort_utils.h"
#include <stdlib.h>
#include <stdio.h>

static int	select_best_bucket_size(const int *sizes,
									int num_buckets,
									int results[])
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
		results[i] = bucket_sort(num_elements, elements, \
								sizes[i], write_instruction);
		++i;
	}
	return (select_best_bucket_size(sizes, num_buckets, results));
}

int	get_elements_from_bucket(t_stack_pair *stacks,
							t_bucket *bucket,
							t_write_instruction write_instruction)
{
	t_index	index;
	int		num_moves;

	num_moves = 0;
	while (bucket->missing_elements)
	{
		index = find_element_index_to_move(stacks, bucket);
		num_moves += move_element_to_stack_b(stacks, index, write_instruction);
		--bucket->missing_elements;
	}
	return (num_moves);
}

int	move_all_elements_back_to_a(t_stack_pair *stacks,
								int num_elements,
								const int *sorted,
								t_write_instruction write_instruction)
{
	int		i;
	int		num_moves;
	t_index	index;

	i = num_elements - 1;
	num_moves = 0;
	while (i >= 0)
	{
		index.value = find_element_index(&(stacks->b), sorted[i]).value;
		num_moves += move_element_to_stack_a(stacks, index, write_instruction);
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
			bucket = get_next_bucket(bucket, bucket_size, \
									sorted, num_elements);
		}
	}
	num_moves += move_all_elements_back_to_a(&stacks, num_elements, \
											sorted, write_instruction);
	free((void *)sorted);
	destroy_stack_pair(&stacks);
	return (num_moves);
}
