#ifndef INSERTION_SORT_H
# define INSERTION_SORT_H
# include "utils.h"
# include <stack/stack.h>
# include <stack/processor.h>

int		push_elements_back_to_stack_a(t_stack_pair *stacks, \
						t_write_instruction write_instruction);
int		move_element_to_stack_b(t_stack_pair *stacks, int element, \
						t_write_instruction write_instruction);
int		find_element_index(t_stack *stack, int element);
int		insertion_sort(int elements_size, int *elements, \
						t_write_instruction write_instruction);
void insert_element(t_stack_pair *stacks, t_write_instruction write_instruction);
#endif