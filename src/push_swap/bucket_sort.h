#ifndef BUCKET_SORT_H
# define BUCKET_SORT_H
# include "utils.h"
# include <stack/stack.h>
# include "sorting_utils.h"
# include "bucket.h"

int					bucket_sort(int num_elements, \
								const int *elements, \
								int bucket_size, \
								t_write_instruction write_instruction);
int					try_many_buckets(int num_elements, \
									const int *elements, \
									t_write_instruction write_instruction);

#endif