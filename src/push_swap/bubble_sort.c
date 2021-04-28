#include "bubble_sort.h"
#include "utils.h"
#include <utils/defs.h>

void	swap_elements(int *cur, int *prev)
{
	const int	tmp = *cur;

	*cur = *prev;
	*prev = tmp;
	print_instruction("sb", 1);
}

int	bubble_sort(int elements_size, int *elements)
{
	int		i;
	int		num_moves;
	t_bool	swapped;

	num_moves = 0;
	if (elements_size < 2)
		return (num_moves);
	swapped = TRUE;
	while (swapped && !is_list_sorted(elements_size, elements))
	{
		i = 1;
		swapped = FALSE;
		num_moves += print_instruction("pb", 1);
		while (i < elements_size)
		{
			num_moves += print_instruction("pb", 1);
			if (elements[i] < elements[i - 1])
			{
				swapped = TRUE;
				swap_elements(&elements[i], &elements[i - 1]);
				++num_moves;
			}
			++i;
		}
		num_moves += print_instruction("pa", elements_size);
	}
	return (num_moves);
}