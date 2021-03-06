#ifndef STACK_H
# define STACK_H
# include <utils/defs.h> 

typedef struct s_stack
{
	int	*elements;
	int	top;
}	t_stack;

void				swap_top_elements(t_stack *stack);
void				push(t_stack *stack, int element);
t_optional_int		pop(t_stack *stack);
void				rotate(t_stack *stack);
void				reverse_rotate(t_stack *stack);
int					size(const t_stack *stack);
t_optional_int		top_element(t_stack *stack);

#endif