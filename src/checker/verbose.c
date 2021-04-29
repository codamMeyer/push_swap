#include "verbose.h"
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
