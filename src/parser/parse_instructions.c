#include "parse_instructions.h"
#include <libft.h>
#include <utils/instructions.h>
#include <utils/status.h>

t_instructions	get_instruction(const char *instruction_string)
{
	if (ft_strncmp(instruction_string, STR_RRA, 4) == 0)
		return (RRA);
	if (ft_strncmp(instruction_string, STR_RRB, 4) == 0)
		return (RRB);
	if (ft_strncmp(instruction_string, STR_RRR, 4) == 0)
		return (RRR);
	if (ft_strncmp(instruction_string, STR_SA, 3) == 0)
		return (SA);
	if (ft_strncmp(instruction_string, STR_SB, 3) == 0)
		return (SB);
	if (ft_strncmp(instruction_string, STR_SS, 3) == 0)
		return (SS);
	if (ft_strncmp(instruction_string, STR_PA, 3) == 0)
		return (PA);
	if (ft_strncmp(instruction_string, STR_PB, 3) == 0)
		return (PB);
	if (ft_strncmp(instruction_string, STR_RA, 3) == 0)
		return (RA);
	if (ft_strncmp(instruction_string, STR_RB, 3) == 0)
		return (RB);
	if (ft_strncmp(instruction_string, STR_RR, 3) == 0)
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

	if (ret == ERROR_GNL)
		instruction = INVALID_INSTRUCTION;
	instruction = get_instruction(instruction_string);
	free(instruction_string);
	return (instruction);
}
