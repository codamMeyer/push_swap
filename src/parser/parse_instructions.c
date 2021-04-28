#include "parse_instructions.h"
#include <utils/status.h>
#include <libft.h>

t_instructions	get_instruction(const char *instruction_string)
{
	if (ft_strncmp(instruction_string, "rra", 3) == 0)
		return (RRA);
	if (ft_strncmp(instruction_string, "rrb", 3) == 0)
		return (RRB);
	if (ft_strncmp(instruction_string, "rrr", 3) == 0)
		return (RRR);
	if (ft_strncmp(instruction_string, "sa", 2) == 0)
		return (SA);
	if (ft_strncmp(instruction_string, "sb", 2) == 0)
		return (SB);
	if (ft_strncmp(instruction_string, "ss", 2) == 0)
		return (SS);
	if (ft_strncmp(instruction_string, "pa", 2) == 0)
		return (PA);
	if (ft_strncmp(instruction_string, "pb", 2) == 0)
		return (PB);
	if (ft_strncmp(instruction_string, "ra", 2) == 0)
		return (RA);
	if (ft_strncmp(instruction_string, "rb", 2) == 0)
		return (RB);
	if (ft_strncmp(instruction_string, "rr", 2) == 0)
		return (RR);
	if (ft_strncmp(instruction_string, "\0", 1) == 0)
		return (END_OF_INSTRUCTIONS);
	return (INVALID_INSTRUCTION);
}

t_instructions	get_next_instruction(void)
{
	t_instructions	instruction;
	char			*instruction_string;
	const int		ret = get_next_line(STDOUT_FILENO, &instruction_string);

	if (ret == ERROR)
		instruction = INVALID_INSTRUCTION;
	instruction = get_instruction(instruction_string);
	free(instruction_string);
	return (instruction);
}
