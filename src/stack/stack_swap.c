#include "stack.h"

void	swap_top_elements(t_stack *stack)
{
	int	tmp;

	if (size(stack) < 2)
		return ;
	tmp = stack->elements[stack->top];
	stack->elements[stack->top] = stack->elements[stack->top - 1];
	stack->elements[stack->top - 1] = tmp;
}
