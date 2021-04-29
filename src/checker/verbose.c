#include "verbose.h"
#include "processor.h"
#include <libft.h>
#include <stdio.h>
#include <fcntl.h>

void	print_final_result(const t_stack *stack_a)
{
	int			i;
	const int	fd = open("result", O_WRONLY | O_CREAT | O_TRUNC, 0777);

	i = stack_a->top;
	while (i >= 0)
	{
		ft_putnbr_fd(stack_a->elements[i], fd);
		ft_putstr_fd(" ", fd);
		--i;
	}
	close(fd);
}

void	print_initial_state(const t_stack *stack_a)
{
	int	i;

	i = stack_a->top;
	printf("\n\n********** INITIAL STATE *********\n\n");
	while (i >= 0)
	{
		printf("  |%3d|\n", stack_a->elements[i]);
		--i;
	}
	printf("\nstack A\n");
}

void	print_rra_state(const t_stack_pair *stacks)
{
	int	i;

	if (stacks->a.top > stacks->b.top)
		i = stacks->a.top;
	else
		i = stacks->b.top;
	printf("\n------ RRA ------\n\n");
	while (i >= 0)
	{
		if (i == stacks->a.top)
			printf("%s|%*d|%s      ", LIGHT_GREEN, 3, \
						stacks->a.elements[i], LIGHT_WHITE);
		else
			printf("%s|%*d|      ", LIGHT_WHITE, 3, stacks->a.elements[i]);
		if (i <= stacks->b.top)
			printf("%s|%*d|\n", LIGHT_WHITE, 3, stacks->b.elements[i]);
		else
			printf("%s\n", LIGHT_WHITE);
		--i;
	}
	printf("\nstack A    stack B\n");
}

void	print_pb_state(const t_stack_pair *stacks)
{
	int	i;

	if (stacks->a.top > stacks->b.top)
		i = stacks->a.top;
	else
		i = stacks->b.top;
	printf("\n------ PB ------\n\n");
	while (i >= 0)
	{
		if (i <= stacks->a.top)
			printf("%s|%*d|      ", LIGHT_WHITE, 3, stacks->a.elements[i]);
		else
			printf("           ");
		if (i == stacks->b.top)
			printf("%s|%*d|%s\n", LIGHT_PURPLE, 3, \
							stacks->b.elements[i], LIGHT_WHITE);
		else if (i < stacks->b.top)
			printf("%s|%*d|%s\n", LIGHT_WHITE, 3, stacks->b.elements[i], \
													LIGHT_WHITE);
		else
			printf("%s\n", LIGHT_WHITE);
		--i;
	}
	printf("\nstack A    stack B\n");
}
