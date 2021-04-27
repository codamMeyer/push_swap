#include "parse_instructions.h"
#include <libft.h>

t_instructions	get_instruction(const char *instruction_string)
{
	if (ft_strncmp(instruction_string, "rra", 3) == 0)
		return (RRA);
	else if (ft_strncmp(instruction_string, "rrb", 3) == 0)
		return (RRB);
	else if (ft_strncmp(instruction_string, "rrr", 3) == 0)
		return (RRR);
	else if (ft_strncmp(instruction_string, "sa", 2) == 0)
		return (SA);
	else if (ft_strncmp(instruction_string, "sb", 2) == 0)
		return (SB);
	else if (ft_strncmp(instruction_string, "ss", 2) == 0)
		return (SS);
	else if (ft_strncmp(instruction_string, "pa", 2) == 0)
		return (PA);
	else if (ft_strncmp(instruction_string, "pb", 2) == 0)
		return (PB);
	else if (ft_strncmp(instruction_string, "ra", 2) == 0)
		return (RA);
	else if (ft_strncmp(instruction_string, "rb", 2) == 0)
		return (RB);
	else if (ft_strncmp(instruction_string, "rr", 2) == 0)
		return (RR);
	return (INVALID_INSTRUCTION);
}
