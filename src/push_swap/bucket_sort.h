#ifndef BUCKET_SORT_H
# define BUCKET_SORT_H
# include "utils.h"
# include <stack/stack.h>
# include "sorting_utils.h"
# include "bucket.h"

t_optional_index	search_stack_top(const t_stack *stack, \
									const t_bucket *bucket);
t_optional_index	search_stack_bottom(const t_stack *stack, \
										const t_bucket *bucket);
int					bucket_sort(int num_elements, \
								const int *elements, \
								t_write_instruction write_instruction);

#endif