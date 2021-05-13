#ifndef VERBOSE_H
# define VERBOSE_H
# define STACK_A_BACKGROUND "\e[48;5;69m\e[4m"
# define STACK_B_BACKGROUND "\e[48;5;29m\e[4m"
# define STACK_A_ACTIVE "\e[48;5;111m\e[4m"
# define STACK_B_ACTIVE "\e[48;5;36m\e[4m"
# define RESET_COLOR "\e[0m"
# include <stack/stack.h>
# include <stack/processor.h>

void	print_stacks(t_stack_pair *stacks, t_instructions instruction);

#endif