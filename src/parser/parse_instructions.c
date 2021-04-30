#include "parse_instructions.h"
#include <utils/status.h>
#include <libft.h>

t_instructions	get_instruction(const char *instruction_string)
{
	if (ft_strncmp(instruction_string, "rra", 4) == 0)
		return (RRA);
	if (ft_strncmp(instruction_string, "rrb", 4) == 0)
		return (RRB);
	if (ft_strncmp(instruction_string, "rrr", 4) == 0)
		return (RRR);
	if (ft_strncmp(instruction_string, "sa", 3) == 0)
		return (SA);
	if (ft_strncmp(instruction_string, "sb", 3) == 0)
		return (SB);
	if (ft_strncmp(instruction_string, "ss", 3) == 0)
		return (SS);
	if (ft_strncmp(instruction_string, "pa", 3) == 0)
		return (PA);
	if (ft_strncmp(instruction_string, "pb", 3) == 0)
		return (PB);
	if (ft_strncmp(instruction_string, "ra", 3) == 0)
		return (RA);
	if (ft_strncmp(instruction_string, "rb", 3) == 0)
		return (RB);
	if (ft_strncmp(instruction_string, "rr", 3) == 0)
		return (RR);
	if (ft_strncmp(instruction_string, "\0", 1) == 0)
		return (END_OF_INSTRUCTIONS);
	return (INVALID_INSTRUCTION);
}

t_instructions	get_next_instruction(void)
{
	t_instructions	instruction;
	char			*instruction_string;
	const int		ret = get_next_line(STDIN_FILENO, &instruction_string);

	if (ret == ERROR)
		instruction = INVALID_INSTRUCTION;
	instruction = get_instruction(instruction_string);
	free(instruction_string);
	return (instruction);
}
