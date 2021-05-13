#ifndef BUCKET_SORT_UTILS_H
# define BUCKET_SORT_UTILS_H
# include <stack/processor.h>
# include "sorting_utils.h"
# include "bucket.h"

t_optional_index	search_stack_top(const t_stack *stack, \
										const t_bucket *bucket);
t_optional_index	search_stack_bottom(const t_stack *stack, \
										const t_bucket *bucket);

t_index				find_element_index_to_move(const t_stack_pair *stacks, \
										const t_bucket *bucket);
int					move_element_to_stack_a(t_stack_pair *stacks, \
								t_index index, \
								t_write_instruction write_instruction);

#endif