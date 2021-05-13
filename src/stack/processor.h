#ifndef PROCESSOR_H
# define PROCESSOR_H
# include "stack.h"
# include <utils/instructions.h>

typedef struct s_stack_pair
{
	t_stack	a;
	t_stack	b;
	t_bool	initialized;
}	t_stack_pair;

void			sa(t_stack_pair *stacks);
void			sb(t_stack_pair *stacks);
void			ss(t_stack_pair *stacks);
void			pa(t_stack_pair *stacks);
void			pb(t_stack_pair *stacks);
void			ra(t_stack_pair *stacks);
void			rb(t_stack_pair *stacks);
void			rr(t_stack_pair *stacks);
void			rra(t_stack_pair *stacks);
void			rrb(t_stack_pair *stacks);
void			rrr(t_stack_pair *stacks);
void			destroy_stack_pair(t_stack_pair *stacks);
t_stack_pair	create_stack_pair(int stack_size);
void			populate_stack_a(const int *elements, \
								int num_elements, \
								t_stack_pair *stacks);
void			process_next_instruction(t_instructions instruction, \
											t_stack_pair *stacks);
#endif