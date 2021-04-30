#include "parse_numbers.h"
#include <libft.h>
#include <limits.h>

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

static t_bool	is_a_valid_number(const char *str_n, long int n)
{
	const int	len = ft_strlen(str_n);
	int			i;

	i = 0;
	if ((str_n[0] == '-' && len > 11) || len == 0)
		return (FALSE);
	if ((str_n[0] != '-' && len > 10))
		return (FALSE);
	if (n > INT_MAX || n < INT_MIN)
		return (FALSE);
	if (str_n[0] == '-')
		++i;
	while (i < len)
	{
		if (!ft_isdigit(str_n[i]))
			return (FALSE);
		++i;
	}
	return (TRUE);
}

int	*parse_numbers( int list_size, const char **list)
{
	int			*stack;
	long int	element;
	int			i;

	stack = malloc(sizeof(int) * list_size);
	i = 0;
	if (!stack)
		return (NULL);
	while (i < list_size)
	{
		element = ft_atoi(list[i]);
		if (!is_a_valid_number(list[i], element) || \
			has_duplicate(stack, element, i))
		{
			free(stack);
			return (NULL);
		}
		stack[i] = element;
		++i;
	}
	return (stack);
}
