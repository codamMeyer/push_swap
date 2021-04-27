#include "processor.h"
#include <stdlib.h>

void	destroy_stack_pair(t_stack_pair *stacks)
{
	if (stacks->initialized)
	{
		free(stacks->a.elements);
		free(stacks->b.elements);
	}
	stacks->initialized = FALSE;
}

t_stack_pair	create_stack_pair(int stack_size)
{
	t_stack_pair	stacks;

	stacks.a.elements = malloc(sizeof(int) * stack_size);
	stacks.b.elements = malloc(sizeof(int) * stack_size);
	stacks.a.top = -1;
	stacks.b.top = -1;
	if (!(stacks.a.elements) || !(stacks.b.elements))
		destroy_stack_pair(&stacks);
	stacks.initialized = TRUE;
	return (stacks);
}

void	populate_stack_a(int *elements, int num_elements, t_stack_pair *stacks)
{
	int	i;

	i = num_elements - 1;
	while (i >= 0)
	{
		push(&(stacks->a), elements[i]);
		--i;
	}
}

void	process_next_instruction(t_instructions instruction,
								t_stack_pair *stacks)
{
	if (instruction == RRA)
		rra(stacks);
	else if (instruction == RRB)
		rrb(stacks);
	else if (instruction == RRR)
		rrr(stacks);
	else if (instruction == SA)
		sa(stacks);
	else if (instruction == SB)
		sb(stacks);
	else if (instruction == SS)
		ss(stacks);
	else if (instruction == PA)
		pa(stacks);
	else if (instruction == PB)
		pb(stacks);
	else if (instruction == RA)
		ra(stacks);
	else if (instruction == RB)
		rb(stacks);
	else
		rr(stacks);
}
