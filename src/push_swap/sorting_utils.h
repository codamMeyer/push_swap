#ifndef SORTING_UTILS_H
# define SORTING_UTILS_H
# include "utils.h"
# include <utils/defs.h>
# include <stack/stack.h>
# include <stack/processor.h>

typedef struct s_optional_index
{
	int		index;
	t_bool	initialized;
}	t_optional_index;

typedef void(*t_operation)(t_stack_pair	*stack);

void				execute_operation(t_stack_pair *stacks,	int counter, t_operation operation);
int					move_element_to_stack_b(t_stack_pair *stacks, int element, t_write_instruction write_instruction);
t_optional_index	find_element_index(t_stack *stack, int element);

#endif