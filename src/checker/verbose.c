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

void	print_stack_a(t_stack *stacks_a, t_instructions instruction, int i)
{
	if ((instruction == PA || instruction == RRA || instruction == RRR) && i == stacks_a->top)
		printf("%s%12d %s       ", STACK_A_ACTIVE, stacks_a->elements[i], RESET_COLOR);
	else if ((instruction == RA || instruction == RA || instruction == RR) && i == 0)
		printf("%s%12d %s       ", STACK_A_ACTIVE, stacks_a->elements[i], RESET_COLOR);
	else if ((instruction == SA || instruction == SS) && (i == stacks_a->top || i == (stacks_a->top - 1)))
		printf("%s%12d %s       ", STACK_A_ACTIVE, stacks_a->elements[i], RESET_COLOR);
	else if (i <= stacks_a->top)
		printf("%s%12d %s       ", STACK_A_BACKGROUND, stacks_a->elements[i], RESET_COLOR);
	else
		printf("%20s", "");
}

void	print_stack_b(t_stack *stacks_b, t_instructions instruction, int i)
{
	if ((instruction == PB || instruction == RRB || instruction == RRR) && i == stacks_b->top)
		printf("%s%12d %s       \n", STACK_B_ACTIVE, stacks_b->elements[i], RESET_COLOR);
	else if ((instruction == RB || instruction == RB || instruction == RR) && i == 0)
		printf("%s%12d %s       \n", STACK_B_ACTIVE, stacks_b->elements[i], RESET_COLOR);
	else if ((instruction == SB || instruction == SS) && (i == stacks_b->top || i == (stacks_b->top - 1)))
		printf("%s%12d %s       \n", STACK_B_ACTIVE, stacks_b->elements[i], RESET_COLOR);
	else if (i <= stacks_b->top)
		printf("%s%12d %s\n", STACK_B_BACKGROUND, stacks_b->elements[i], RESET_COLOR);
	else
		printf("\n");
}

void	print_stacks(t_stack_pair *stacks, t_instructions instruction)
{
	int	i;

	i = get_tallest_stack(stacks);
	printf("\n---------------------------------------------------\n\n");
	while (i >= 0)
	{
		print_stack_a(&(stacks->a), instruction, i);
		print_stack_b(&(stacks->b), instruction, i);
		--i;
	}
	printf("\n   Stack A             Stack B\n");
}
