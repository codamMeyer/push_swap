#ifndef CHECKER_H
# define CHECKER_H
# include "processor.h"

typedef t_instructions(*t_get_next_instruction)();

t_status		is_stack_sorted(const t_stack *stack_a);
t_status		run_checker(int stack_size, const char *elements[], \
							t_get_next_instruction next_instruction);
#endif