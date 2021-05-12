#include "utils.h"
#include <unistd.h>
#include <libft.h>

void	swap_elements(int *cur, int *prev)
{
	const int	tmp = *cur;

	*cur = *prev;
	*prev = tmp;
}

t_bool	is_descending_order(int num_elements, const int *elements)
{
	int	i;

	i = 1;
	while (i < num_elements)
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
		write(STDOUT_FILENO, "\n", 1);
		++i;
	}
}

int	*sort_elements(int num_elements, const int *elements)
{
	int		i;
	t_bool	swapped;
	int		*sorted;

	sorted = malloc(sizeof(int) * num_elements);
	if (sorted == NULL)
		return (NULL);
	sorted = ft_memcpy(sorted, elements, num_elements * sizeof(int));
	swapped = TRUE;
	while (swapped)
	{
		swapped = FALSE;
		i = 1;
		while (i < num_elements)
		{
			if (sorted[i] < sorted[i - 1])
			{
				swapped = TRUE;
				swap_elements(&sorted[i], &sorted[i - 1]);
			}
			++i;
		}
	}
	return (sorted);
}
