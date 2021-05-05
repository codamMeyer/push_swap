#include "processor.h"

void	sa(t_stack_pair *stacks)
{
	swap_top_elements(&(stacks->a));
}

void	sb(t_stack_pair *stacks)
{
	swap_top_elements(&(stacks->b));
}

void	ss(t_stack_pair *stacks)
{
	sa(stacks);
	sb(stacks);
}
