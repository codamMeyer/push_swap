#include "verbose.h"
#include "processor.h"
#include <stdio.h>
#include <ft_printf.h>
#include <fcntl.h>

int	get_tallest_stack(t_stack_pair *stacks)
{
	if (stacks->a.top > stacks->b.top)
		return (stacks->a.top);
	return (stacks->b.top);
}

void	print_stack_element(char *color, int i)
{
	ft_printf("%s%12d %s       ", color, i, RESET_COLOR);
}

void	print_stack_a(t_stack *stack, t_instructions inst, int i)
{
	const t_bool	highlight_top = \
		((inst == PA || inst == RRA || inst == RRR) && i == stack->top);
	const t_bool	highlight_bottom = ((inst == RA || inst == RR) && i == 0);
	const t_bool	highlight_first_two = ((inst == SA || inst == SS) && \
							(i == stack->top || i == (stack->top - 1)));

	if (highlight_top)
		print_stack_element(STACK_A_ACTIVE, stack->elements[i]);
	else if (highlight_bottom)
		print_stack_element(STACK_A_ACTIVE, stack->elements[i]);
	else if (highlight_first_two)
		print_stack_element(STACK_A_ACTIVE, stack->elements[i]);
	else if (i <= stack->top)
		print_stack_element(STACK_A_BACKGROUND, stack->elements[i]);
	else
		ft_printf("%20s", "");
}

void	print_stack_b(t_stack *stack, t_instructions inst, int i)
{
	const t_bool	highlight_top = \
		((inst == PB || inst == RRB || inst == RRR) && i == stack->top);
	const t_bool	highlight_bottom = ((inst == RB || inst == RR) && i == 0);
	const t_bool	highlight_first_two = ((inst == SB || inst == SS) && \
							(i == stack->top || i == (stack->top - 1)));

	if (highlight_top)
		print_stack_element(STACK_B_ACTIVE, stack->elements[i]);
	else if (highlight_bottom)
		print_stack_element(STACK_B_ACTIVE, stack->elements[i]);
	else if (highlight_first_two)
		print_stack_element(STACK_B_ACTIVE, stack->elements[i]);
	else if (i <= stack->top)
		print_stack_element(STACK_B_BACKGROUND, stack->elements[i]);
	ft_printf("\n");
}

void	print_stacks(t_stack_pair *stacks, t_instructions instruction)
{
	int	i;

	i = get_tallest_stack(stacks);
	ft_printf("\n---------------------------------------------------\n\n");
	while (i >= 0)
	{
		print_stack_a(&(stacks->a), instruction, i);
		print_stack_b(&(stacks->b), instruction, i);
		--i;
	}
	ft_printf("\n   Stack A             Stack B\n");
}
