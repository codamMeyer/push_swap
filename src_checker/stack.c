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
	const int	stack_size = size(stack);
	int			tmp;
	int			i;

	if (stack_size < 2)
		return ;
	tmp = stack->elements[stack->top];
	i = stack_size - 1;
	while (i > 0)
	{
		stack->elements[i] = stack->elements[i - 1];
		--i;
	}
	stack->elements[i] = tmp;
}
