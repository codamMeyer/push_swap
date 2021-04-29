#ifndef VERBOSE_H
# define VERBOSE_H
# include "stack.h"
# include "processor.h"
# define DARK_GRAY "\e[1;30m"
# define LIGHT_RED "\e[1;31m"
# define LIGHT_GREEN "\e[1;32m"
# define YELLOW "\e[1;33m"
# define LIGHT_BLUE "\e[1;34m"
# define LIGHT_PURPLE "\e[1;35m"
# define LIGHT_CYAN "\e[1;36m"
# define LIGHT_WHITE "\e[1;37m"

void	print_final_result(const t_stack *stack_a);
void	print_initial_state(const t_stack *stack_a);
void	print_rra_state(const t_stack_pair *stacks);
void	print_pb_state(const t_stack_pair *stacks);

#endif