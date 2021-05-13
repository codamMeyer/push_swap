#ifndef BUCKET_SORT_H
# define BUCKET_SORT_H
# include "bucket.h"
# include "sorting_utils.h"
# include "utils.h"
# include <stack/stack.h>

int					bucket_sort(int num_elements, \
								const int *elements, \
								int bucket_size, \
								t_write_instruction write_instruction);
int					try_many_buckets(int num_elements, \
									const int *elements, \
									t_write_instruction write_instruction);

#endif