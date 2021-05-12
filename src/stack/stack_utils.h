#ifndef STACK_UTILS_H
# define STACK_UTILS_H
# include <utils/status.h>
# include "stack.h"

typedef t_bool	(*t_compare)(int, int);

t_bool		is_ascending(int top, int bottom);
t_bool		is_sorted(const t_stack *stack, t_compare compare);
t_status	is_stack_sorted(const t_stack *stack_a, int initial_size);

#endif