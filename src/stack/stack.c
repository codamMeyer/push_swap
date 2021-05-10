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
	int			tmp;
	int			i;

	if (size(stack) < 2)
		return ;
	tmp = stack->elements[stack->top];
	i = stack->top;
	while (i > 0)
	{
		stack->elements[i] = stack->elements[i - 1];
		--i;
	}
	stack->elements[i] = tmp;
}

void	reverse_rotate(t_stack *stack)
{
	const int	stack_size = size(stack);
	int			tmp;
	int			i;

	if (stack_size < 2)
		return ;
	tmp = stack->elements[0];
	i = 0;
	while (i < stack_size - 1)
	{
		stack->elements[i] = stack->elements[i + 1];
		++i;
	}
	stack->elements[i] = tmp;
}

t_optional_int	pop(t_stack *stack)
{
	t_optional_int	element;

	if (!size(stack))
	{
		element.initialized = FALSE;
		return (element);
	}
	element.element = stack->elements[stack->top];
	element.initialized = TRUE;
	--(stack->top);
	return (element);
}

t_optional_int	top_element(t_stack *stack)
{
	t_optional_int	element;

	if (!size(stack))
	{
		element.initialized = FALSE;
		return (element);
	}
	element.element = stack->elements[stack->top];
	element.initialized = TRUE;
	return (element);
}
