#include "processor.h"

void sa(t_stack_pair *stacks)
{
	swap_top_elements(&(stacks->a));
}

void sb(t_stack_pair *stacks)
{
	swap_top_elements(&(stacks->b));
}

void ss(t_stack_pair *stacks)
{
	sa(stacks);
	sb(stacks);
}

void pa(t_stack_pair *stacks)
{
	const t_optional_int element = pop(&(stacks->b));
	if (element.initialized)
		push(&(stacks->a), element.element);
}

void pb(t_stack_pair *stacks)
{
	const t_optional_int element = pop(&(stacks->a));
	if (element.initialized)
		push(&(stacks->b), element.element);
}

void ra(t_stack_pair *stacks)
{
	rotate(&(stacks->a));
}

void rb(t_stack_pair *stacks)
{
	rotate(&(stacks->b));
}

void rr(t_stack_pair *stacks)
{
	ra(stacks);
	rb(stacks);
}

void rra(t_stack_pair *stacks)
{
	reverse_rotate(&(stacks->a));
}

void rrb(t_stack_pair *stacks)
{
	reverse_rotate(&(stacks->b));
}

void rrr(t_stack_pair *stacks)
{
	rra(stacks);
	rrb(stacks);
}
