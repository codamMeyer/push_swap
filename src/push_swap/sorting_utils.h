#ifndef SORTING_UTILS_H
# define SORTING_UTILS_H
# include "utils.h"
# include <stack/processor.h>
# include <stack/stack.h>
# include <utils/defs.h>

typedef struct s_index
{
	int		value;
}	t_index;

typedef struct s_optional_index
{
	int		value;
	t_bool	initialized;
}	t_optional_index;

typedef void(*t_operation)(t_stack_pair	*stack);

t_bool				is_close_to_top(const t_stack *stack, t_index index);
void				execute_operation(t_stack_pair *stacks, \
										int counter, \
										t_operation operation);
int					move_element_to_stack_b(t_stack_pair *stacks, \
										t_index index, \
										t_write_instruction write_instruction);
t_optional_index	find_element_index(t_stack *stack, int element);

#endif