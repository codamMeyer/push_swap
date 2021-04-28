#include "push_swap.h"
#include "bubble_sort.h"
#include "utils.h"
#include <utils/defs.h>
#include <parser/parse_numbers.h>
#include <stdlib.h>

static void generate_algorthm(int elements_size, int *elements)
{
	bubble_sort(elements_size, elements, print_instruction);
}

t_status	run_push_swap(int elements_size, const char *elements[])
{
	int				*elements_list;
	t_status		ret;

	ret = OK;
	elements_list = parse_numbers(elements_size, elements);
	if (!elements_list)
		ret = ERROR;
	if (ret != ERROR)
		generate_algorthm(elements_size, elements_list);
	free(elements_list);
	return (ret);
}
