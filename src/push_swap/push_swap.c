#include "push_swap.h"
#include "bubble_sort.h"
#include <stdio.h>
#include <utils/defs.h>
#include <parser/parse_numbers.h>
#include <stdlib.h>

/* static void generate_algorthm(elements_size, elements)
** {
**     (void)elements_size;
**     (void)elements;
** }
*/

t_status	run_push_swap(int elements_size, const char *elements[])
{
	int				*elements_list;
	t_status		ret;

	ret = OK;
	elements_list = parse_numbers(elements_size, elements);
	if (!elements_list)
		ret = ERROR;
	free(elements_list);
	return (ret);
}
