#include "checker.h"
#include <parser/parse_instructions.h>
#include <parser/parse_numbers.h>
#include <parser/parse_flags.h>
#include "verbose.h"
#include "write_result.h"
#include <utils/status.h>
#include <stack/stack_utils.h>
#include <stdlib.h>
#include <libft.h>
#include <ft_printf.h>
#include <stdio.h>

static t_status	process_instructions_list(t_stack_pair *stacks, \
									t_flags flags,
									t_get_next_instruction next_instruction)
{
	t_instructions	instruction;
	int				counter;

	counter = 0;
	if (flags.verbose)
		print_stacks(stacks, INVALID_INSTRUCTION);
	while (TRUE)
	{
		instruction = next_instruction();
		if (instruction == INVALID_INSTRUCTION)
			return (ERROR);
		if (instruction == END_OF_INSTRUCTIONS)
			break ;
		process_next_instruction(instruction, stacks);
		if (flags.verbose)
			print_stacks(stacks, instruction);
		++counter;
	}
	if (flags.total)
		ft_printf("total moves: %d\n", counter);
	return (OK);
}

t_status	is_valid_solution(const t_stack *stack_a, int initial_size)
{
	const int	stack_size = size(stack_a);

	if (stack_size != initial_size || !is_sorted(stack_a, is_ascending))
		return (KO);
	return (OK);
}

t_status	run_checker(int size,
						const char *argv[],
						t_get_next_instruction next_instruction)
{
	int				i;
	t_flags			flags;
	int				*stack_elements;
	t_stack_pair	stacks;
	t_status		ret;

	i = 0;
	flags = parse_flags(argv, &size, &i);
	if (!flags.is_valid)
		return (ERROR);
	ret = ERROR;
	stack_elements = parse_numbers(size, &argv[i]);
	stacks = create_stack_pair(size);
	if (stack_elements && stacks.initialized)
	{
		populate_stack_a(stack_elements, size, &stacks);
		ret = process_instructions_list(&stacks, flags, next_instruction);
	}
	if (ret != ERROR)
		ret = is_valid_solution(&(stacks.a), size);
	if (flags.file_output)
		write_final_result_in_file(&(stacks.a));
	destroy_stack_pair(&stacks);
	free(stack_elements);
	return (ret);
}
