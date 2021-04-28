#include "utils.h"
#include <stdio.h>

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