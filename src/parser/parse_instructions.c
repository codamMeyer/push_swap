#include "parse_instructions.h"
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
	return (INVALID_INSTRUCTION);
}

// t_instructions parse_next_instruction()
// {
// 	// char *line;


// 	//get next line
// 	//return get_instruction(line); 
// }