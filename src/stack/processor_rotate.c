#include "processor.h"

void	ra(t_stack_pair *stacks)
{
	rotate(&(stacks->a));
}

void	rb(t_stack_pair *stacks)
{
	rotate(&(stacks->b));
}

void	rr(t_stack_pair *stacks)
{
	ra(stacks);
	rb(stacks);
}
