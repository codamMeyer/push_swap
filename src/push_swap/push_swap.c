#include "push_swap.h"
#include "insertion_sort.h"
#include "bucket_sort.h"
#include "utils.h"
#include "special_cases_sort.h"
#include <utils/defs.h>
#include <parser/parse_numbers.h>
#include <stdlib.h>
#include <stdio.h>

t_bool	is_list_sorted(int num_elements, const int *elements)
{
	int	i;

	i = 1;
	if (!elements)
		return (FALSE);
	while (i < num_elements)
	{
		if (elements[i] < elements[i - 1])
			return (FALSE);
		++i;
	}
	return (TRUE);
}

static void	fake(const char *instruction, int times)
{
	(void)instruction;
	(void)times;
}

static void	generate_algorthm(int num_elements, const int *elements)
{
	int	total_insertion;
	int	bucket_size;
	int	total_bucket;

	total_insertion = 0;
	total_bucket = 0;
	if (is_list_sorted(num_elements, elements))
		return ;
	if (is_descending_order(num_elements, elements))
		from_descending_to_ascending_order(num_elements, print_instruction);
	else if (num_elements <= 5)
		insertion_sort(num_elements, elements, print_instruction);
	else
	{
		total_insertion = insertion_sort(num_elements, elements, fake);
		bucket_size = try_many_buckets(num_elements, elements, fake);
		total_bucket = bucket_sort(num_elements, elements, bucket_size, fake);
		if (total_insertion < total_bucket)
			insertion_sort(num_elements, elements, print_instruction);
		else
			bucket_sort(num_elements, elements, bucket_size, print_instruction);
	}
}

t_status	run_push_swap(int num_elements, const char *elements[])
{
	int				*elements_list;
	t_status		ret;

	ret = OK;
	elements_list = parse_numbers(num_elements, elements);
	if (!elements_list)
		ret = ERROR;
	if (ret != ERROR)
		generate_algorthm(num_elements, elements_list);
	free(elements_list);
	return (ret);
}
