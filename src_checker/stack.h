#ifndef STACK_H
# define STACK_H

typedef struct s_stack
{
	int	elements[100];
	int	top;
}	t_stack;

void	swap_top_elements(t_stack *stack); // uses pop and push
void	push(t_stack *stack, int element);
int		pop(t_stack *stack);
void	rotate(t_stack *stack); // push and pop
void	reverse_rotate(t_stack *stack); // push and pop
int		size(const t_stack *stack);

#endif