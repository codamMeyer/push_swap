#ifndef BUCKET_SORT_H
# define BUCKET_SORT_H
# include "utils.h"
# include <stack/stack.h>
#include "sorting_utils.h"

typedef struct s_bucket
{
	int		missing_elements;
	int		min_value;
	int		max_value;
	int		start_index;
	int		end_index;
	t_bool	is_valid;
}	t_bucket;

t_bucket			create_bucket(int bucket_size, \
									const int *sorted);
int					get_bucket_size(int num_elements);
t_bucket			get_next_bucket(t_bucket bucket, \
									int bucket_size, \
									const int *sorted, \
									int num_elements);
t_optional_index	search_stack_top(const t_stack *stack, \
									const t_bucket *bucket);
t_optional_index	search_stack_bottom(const t_stack *stack, \
										const t_bucket *bucket);
int					bucket_sort(int num_elements, \
								const int *elements, \
								t_write_instruction write_instruction);

#endif