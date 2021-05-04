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
# define BLUE_BACKGROUND "\e[48;5;69m\e[4m"
# define GREEN_BACKGROUND "\e[48;5;29m\e[4m"
# define RESET_COLOR "\e[0m"

void	write_final_result_in_file(const t_stack *stack_a);
void	print_stacks(t_stack_pair *stacks);

#endif