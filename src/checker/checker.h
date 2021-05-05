#ifndef CHECKER_H
# define CHECKER_H
# include <stack/processor.h>
# include <utils/status.h>

typedef t_instructions(*t_get_next_instruction)();

t_status		is_stack_sorted(const t_stack *stack_a, int initial_size);
t_status		run_checker(int size, const char *argv[], \
						t_get_next_instruction next_instruction);
#endif