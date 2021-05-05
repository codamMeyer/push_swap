#include "processor.h"

void	rra(t_stack_pair *stacks)
{
	reverse_rotate(&(stacks->a));
}

void	rrb(t_stack_pair *stacks)
{
	reverse_rotate(&(stacks->b));
}

void	rrr(t_stack_pair *stacks)
{
	rra(stacks);
	rrb(stacks);
}
