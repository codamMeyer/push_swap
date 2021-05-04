#include "verbose.h"
#include "processor.h"
#include <libft.h>
#include <stdio.h>
#include <fcntl.h>

void	write_final_result_in_file(const t_stack *stack_a)
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

int	get_tallest_stack(t_stack_pair *stacks)
{
	if (stacks->a.top > stacks->b.top)
		return (stacks->a.top);
	return (stacks->b.top);
}

void	print_stacks(t_stack_pair *stacks)
{
	int	i;

	i = get_tallest_stack(stacks);
	printf("\n------------------------------------------------\n\n");
	while (i >= 0)
	{
		if (i <= stacks->a.top)
			printf("%s%12d %s       ", BLUE_BACKGROUND, stacks->a.elements[i], RESET_COLOR);
		else
			printf("%20s", "");
		if (i <= stacks->b.top)
			printf("%s%12d %s\n", GREEN_BACKGROUND, stacks->b.elements[i], RESET_COLOR);
		else
			printf("\n");
		--i;
	}
	printf("\n   Stack A             Stack B\n");
}
