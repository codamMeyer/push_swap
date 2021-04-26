#ifndef PROCESSOR_H
# define PROCESSOR_H
# include "stack.h"

typedef enum e_process
{
	SA = 0,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR,
}	t_process;

typedef struct s_stack_pair
{
	t_stack	a;
	t_stack	b;
}	t_stack_pair;

void	sa(t_stack_pair *stacks);
void	sb(t_stack_pair *stacks);
void	ss(t_stack_pair *stacks);
void	pa(t_stack_pair *stacks);
void	pb(t_stack_pair *stacks);
void	ra(t_stack_pair *stacks);
void	rb(t_stack_pair *stacks);
void	rr(t_stack_pair *stacks);
void	rra(t_stack_pair *stacks);
void	rrb(t_stack_pair *stacks);
void	rrr(t_stack_pair *stacks);

#endif