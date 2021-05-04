#include <inc/int_to_hex_helpers.h>
#include <libft/libft.h>

static void	convert_to_upper(char *to_print, int size)
{
	int	i;

	i = 0;
	while (i <= size)
	{
		to_print[i] = ft_toupper(to_print[i]);
		++i;
	}
}

static int	convert_number(char *numbers_to_print, unsigned int nbr)
{
	unsigned int	remainder;
	unsigned int	result;
	const int		base_size = 16;
	const char		*base = "0123456789abcdef";
	int				i;

	i = 0;
	result = nbr;
	if (nbr == 0)
	{
		numbers_to_print[i] = base[0];
		++i;
	}
	while (result > 0)
	{
		remainder = result % base_size;
		result = result / base_size;
		numbers_to_print[i] = base[remainder];
		++i;
	}
	return (i);
}

static int	convert_long_number(char *numbers_to_print,
									unsigned long int nbr)
{
	unsigned long int	remainder;
	unsigned long int	result;
	const int			base_size = 16;
	const char			*base = "0123456789abcdef";
	int					i;

	i = 0;
	result = nbr;
	while (result > 0)
	{
		remainder = result % base_size;
		result = result / base_size;
		numbers_to_print[i] = base[remainder];
		++i;
	}
	return (i);
}

char	*put_number(unsigned int nbr, int to_upper)
{
	char	numbers_to_print[200];
	char	*num;
	int		num_size;
	int		i;

	num_size = convert_number(&numbers_to_print[0], nbr);
	if (to_upper)
		convert_to_upper(&numbers_to_print[0], num_size);
	num = ft_calloc(num_size + 1, sizeof(char));
	--num_size;
	i = 0;
	while (num_size >= 0)
	{
		num[i] = numbers_to_print[num_size];
		++i;
		--num_size;
	}
	return (num);
}

char	*put_long_number(unsigned long int nbr, int to_upper)
{
	char	numbers_to_print[200];
	char	*num;
	int		num_size;
	int		i;

	num_size = convert_long_number(&numbers_to_print[0], nbr);
	if (to_upper)
		convert_to_upper(&numbers_to_print[0], num_size);
	num = ft_calloc(num_size + 1, sizeof(char));
	--num_size;
	i = 0;
	while (num_size >= 0)
	{
		num[i] = numbers_to_print[num_size];
		++i;
		--num_size;
	}
	return (num);
}
