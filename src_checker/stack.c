#include "stack.h"

int	size(const t_stack *stack)
{
	return (stack->top + 1);
}

void	push(t_stack *stack, int element)
{
	++(stack->top);
	stack->elements[stack->top] = element;
}

void	rotate(t_stack *stack)
{
	if (size(stack) < 2)
		return ;
}
