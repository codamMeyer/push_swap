#include "libft.h"

static int	is_space(char a)
{
	if (a == ' ' || a == '\f' || a == '\n')
		return (1);
	if (a == '\r' || a == '\t' || a == '\v')
		return (1);
	return (0);
}

static int	find_first_number(const char *nptr, int *sign)
{
	int	i;

	i = 0;
	while (is_space(nptr[i]))
		++i;
	if (nptr[i] == '-')
	{
		*sign *= -1;
		++i;
	}
	else if (nptr[i] == '+')
		++i;
	return (i);
}

static int	get_overflowed_result(int sign)
{
	if (sign == 1)
		return (-1);
	else
		return (0);
}

long int	ft_atoi(const char *nptr)
{
	int			sign;
	int			index;
	long int	result;

	result = 0;
	sign = 1;
	index = find_first_number(nptr, &sign);
	while (ft_isdigit(nptr[index]))
	{
		if (result > (LONG_MAX / 10))
			return (get_overflowed_result(sign));
		result = (nptr[index] - '0') + (result * 10);
		++index;
	}
	return ((result * sign));
}
