#ifndef INSERTION_SORT_H
# define INSERTION_SORT_H
# include "utils.h"
# include <stack/stack.h>
# include <stack/processor.h>

int	push_elements_back_to_stack_a(t_stack_pair *stacks, \
						t_write_instruction write_instruction);
int	move_element_to_stack_b(t_stack_pair *stacks, int element, \
						t_write_instruction write_instruction);
int	insertion_sort(int num_elements, const int *elements, \
						t_write_instruction write_instruction);

#endif