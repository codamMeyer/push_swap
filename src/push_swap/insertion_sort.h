#ifndef INSERTION_SORT_H
# define INSERTION_SORT_H
# include "utils.h"
# include <stack/stack.h>
# include <stack/processor.h>

int	insertion_sort(int num_elements, const int *elements, \
						t_write_instruction write_instruction);

#endif