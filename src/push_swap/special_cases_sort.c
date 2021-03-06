#include "special_cases_sort.h"
#include <utils/instructions.h>

int	from_descending_to_ascending_order(int num_elements,
										t_write_instruction write_instruction)
{
	int	num_moves;
	int	i;

	if (num_elements < 2)
		return (0);
	num_moves = 0;
	i = 0;
	while (i < num_elements - 2)
	{
		write_instruction(STR_RRA, 1);
		++num_moves;
		write_instruction(STR_PB, 1);
		++num_moves;
		++i;
	}
	write_instruction(STR_SA, 1);
	++num_moves;
	write_instruction(STR_PA, i);
	num_moves += i;
	return (num_moves);
}
