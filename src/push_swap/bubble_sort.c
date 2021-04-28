#include "bubble_sort.h"
#include "utils.h"
#include <utils/defs.h>

void	swap_elements(int *cur, int *prev)
{
	const int	tmp = *cur;

	*cur = *prev;
	*prev = tmp;
}

int	bubble_sort(int elements_size,
				int *elements,
				t_write_instruction write_instruction)
{
	int		i;
	int		num_moves;

	num_moves = 0;
	while (!is_list_sorted(elements_size, elements))
	{
		i = 1;
		write_instruction(STR_PB, 1);
		++num_moves;
		while (i < elements_size)
		{
			write_instruction(STR_PB, 1);
			++num_moves;
			if (elements[i] < elements[i - 1])
			{
				swap_elements(&elements[i], &elements[i - 1]);
				write_instruction(STR_SB, 1);
				++num_moves;
			}
			++i;
		}
		write_instruction(STR_PA, elements_size);
		num_moves += elements_size;
	}
	return (num_moves);
}
