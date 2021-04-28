#include "push_swap.h"
#include <stdio.h>
#include <utils/defs.h>
#include <parser/parse_numbers.h>
#include <stdlib.h>

t_bool	is_list_sorted(int elements_size, int *elements)
{
	int	i;

	i = 1;
	while (i < elements_size)
	{
		if (elements[i] < elements[i - 1])
			return (FALSE);
		++i;
	}
	return (TRUE);
}

int	print_instruction(const char *instruction, int times)
{
	int	i;

	i = 0;
	while (i < times)
	{
		printf("%s\n", instruction);
		++i;
	}
	return (i);
}

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

// static void generate_algorthm(elements_size, elements)
// {
//     (void)elements_size;
//     (void)elements;
// }

t_status	run_push_swap(int elements_size, const char *elements[])
{
	int				*elements_list;
	t_status		ret;

	ret = OK;
	elements_list = parse_numbers(elements_size, elements);
	if (!elements_list)
		ret = ERROR;
	// if (ret != ERROR)
	// 	// generate_algorthm(elements_size, elements);
	free(elements_list);
	return (ret);
}
