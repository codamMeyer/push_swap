#include "push_swap.h"
#include <stdio.h>
#include <utils/defs.h>
#include <parser/parse_numbers.h>
#include <stdlib.h>

t_bool is_list_sorted(int elements_size, int *elements)
{
    int i;

    i = 1;
    while (i < elements_size)
    {
        if (elements[i] < elements[i - 1])
            return (FALSE);
        ++i;
    }
    return (TRUE);
}
int bubble_sort(int elements_size, int *elements)
{
    int     i;
    int     num_moves;
    t_bool  swapped;

    num_moves = 0;
    if (elements_size < 2 || is_list_sorted(elements_size, elements))
        return (num_moves);
    swapped = TRUE;
    printf("\n");
    while (swapped)
    {
        i = 1;
        swapped = FALSE;
        ++num_moves;
        printf("\033[01;35mpb\n");
        while (i < elements_size)
        {
            printf("\033[01;35mpb\n");
            ++num_moves;
            if (elements[i] < elements[i - 1])
            {
                swapped = TRUE;
                int tmp = elements[i];
                elements[i] = elements[i - 1];
                elements[i - 1] = tmp;
                printf("\033[01;33msb\n");
                ++num_moves;
            }
            ++i;
        }
        for (int j = 0; j < elements_size; ++j)
        {
            printf("\033[01;32mpa\n");
            ++num_moves;
        }
    }
    printf("total moves: %d\n", num_moves);
    return (num_moves);
}
// static void generate_algorthm(elements_size, elements)
// {
//     (void)elements_size;
//     (void)elements;
// }

t_status run_push_swap(int elements_size, const char *elements[])
{
	int				*elements_list;
	t_status		ret;

	ret = OK;
	elements_list = parse_numbers(elements_size, elements);
	if (!elements_list)
		ret = ERROR;
	if (ret != ERROR)
        // generate_algorthm(elements_size, elements);
	free(elements_list);
	return (ret);
}