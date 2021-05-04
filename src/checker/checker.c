#include "checker.h"
#include "../parser/parse_instructions.h"
#include "../parser/parse_numbers.h"
#include "verbose.h"
#include <utils/status.h>
#include <stdlib.h>
#include <libft.h>
#include <stdio.h>

t_status	is_stack_sorted(const t_stack *stack_a, int initial_size)
{
	const int	stack_size = size(stack_a);
	int			i;

	i = 1;
	if (stack_size != initial_size)
		return (KO);
	while (i < stack_size)
	{
		if (stack_a->elements[i] > stack_a->elements[i - 1])
		{
			write_final_result_in_file(stack_a);
			return (KO);
		}
		++i;
	}
	write_final_result_in_file(stack_a);
	return (OK);
}

static t_status	process_instructions_list(t_stack_pair *stacks, \
									t_get_next_instruction next_instruction)
{
	t_instructions	instruction;
	int				counter;
	
	counter = 0;
	while (TRUE)
	{
		instruction = next_instruction();
		if (instruction == INVALID_INSTRUCTION)
			return (ERROR);
		if (instruction == END_OF_INSTRUCTIONS)
			break ;
		process_next_instruction(instruction, stacks);
		print_stacks(stacks);
		++counter;
	}
	printf("total moves: %d\n", counter);
	return (OK);
}	

t_status	run_checker(int stack_size,
						const char *elements[],
						t_get_next_instruction next_instruction)
{
	int				*elements_list;
	t_stack_pair	stacks;
	t_status		ret;

	ret = OK;
	elements_list = parse_numbers(stack_size, elements);
	stacks = create_stack_pair(stack_size);
	if (!elements_list || !stacks.initialized)
		ret = ERROR;
	if (ret != ERROR)
	{
		populate_stack_a(elements_list, stack_size, &stacks);
		ret = process_instructions_list(&stacks, next_instruction);
	}
	if (ret != ERROR)
		ret = is_stack_sorted(&(stacks.a), stack_size);
	destroy_stack_pair(&stacks);
	free(elements_list);
	return (ret);
}
