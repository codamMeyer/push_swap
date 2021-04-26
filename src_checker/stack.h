#ifndef STACK_H
# define STACK_H
# define TRUE 1
# define FALSE 0

typedef int	t_bool;

typedef struct s_stack
{
	int	elements[100];
	int	top;
}	t_stack;

typedef struct s_optional_int
{
	int		element;
	t_bool	initialized;
}	t_optional_int;

void				swap_top_elements(t_stack *stack);
void				push(t_stack *stack, int element);
t_optional_int		pop(t_stack *stack);
void				rotate(t_stack *stack);
void				reverse_rotate(t_stack *stack);
int					size(const t_stack *stack);

#endif