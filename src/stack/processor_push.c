#include "processor.h"

void	pa(t_stack_pair *stacks)
{
	const t_optional_int	element = pop(&(stacks->b));

	if (element.initialized)
		push(&(stacks->a), element.element);
}

void	pb(t_stack_pair *stacks)
{
	const t_optional_int	element = pop(&(stacks->a));

	if (element.initialized)
		push(&(stacks->b), element.element);
}
