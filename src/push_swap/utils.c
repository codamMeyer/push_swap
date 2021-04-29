#include "utils.h"
#include <unistd.h>
#include <libft.h>

void	swap_elements(int *cur, int *prev)
{
	const int	tmp = *cur;

	*cur = *prev;
	*prev = tmp;
}

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

t_bool	is_descending_order(int elements_size, int *elements)
{
	int	i;

	i = 1;
	while (i < elements_size)
	{
		if (elements[i] > elements[i - 1])
			return (FALSE);
		++i;
	}
	return (TRUE);
}

void	print_instruction(const char *instruction, int times)
{
	int	i;

	i = 0;
	while (i < times)
	{
		write(STDOUT_FILENO, instruction, ft_strlen(instruction));
		++i;
	}
}
