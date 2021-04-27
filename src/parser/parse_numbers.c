#include "parse_numbers.h"
#include <libft.h>

static t_bool	has_duplicate(int *elements, int element, int cur_size)
{
	int	i;

	i = 0;
	while (i < cur_size)
	{
		if (elements[i] == element)
			return (TRUE);
		++i;
	}
	return (FALSE);
}

static t_bool	is_a_valid_number(const char *element)
{
	const int	len = ft_strlen(element);
	int			i;

	i = 0;
	if (len > 11 || len == 0)
		return (FALSE);
	if (element[0] == '-')
		++i;
	while (i < len)
	{
		if (!ft_isdigit(element[i]))
			return (FALSE);
		++i;
	}
	return (TRUE);
}

int	*parse_numbers( int list_size, const char **list)
{
	int	*stack;
	int	element;
	int	i;

	stack = malloc(sizeof(int) * list_size);
	i = 0;
	if (!stack)
		return (NULL);
	while (i < list_size)
	{
		element = ft_atoi(list[i]);
		if (!is_a_valid_number(list[i]) || has_duplicate(stack, element, i))
		{
			free(stack);
			return (NULL);
		}
		stack[i] = element;
		++i;
	}
	return (stack);
}
