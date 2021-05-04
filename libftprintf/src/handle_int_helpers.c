#include <inc/handle_int_helpers.h>
#include <inc/math.h>
#include <libft/libft.h>

static int	ft_num_len(long n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		++len;
		n *= -1;
	}
	while (n > 0)
	{
		++len;
		n /= 10;
	}
	return (len);
}

char	*unsigned_to_string(unsigned int nb)
{
	char	*num_str;
	long	n;
	int		len;

	n = nb;
	len = ft_num_len(n);
	num_str = (char *)ft_calloc((len + 1), sizeof(char));
	if (num_str == NULL)
		return (NULL);
	len--;
	if (n == 0)
	{
		num_str[0] = '0';
		return (num_str);
	}
	while (n > 0)
	{
		num_str[len] = '0' + (n % 10);
		n /= 10;
		len--;
	}
	return (num_str);
}

void	check_if_negative(int *n, t_flag *cur_flag)
{
	if (*n < 0 && *n != INT_MIN)
	{
		*n *= -1;
		cur_flag->is_negative = TRUE;
	}
}

int	calculate_num_len(int n, char *num, t_flag *cur_flag)
{
	if (cur_flag->precision == 0 && n == 0)
		return (0);
	return (ft_strlen(num));
}

int	calculate_char_count(int num_len, t_flag *cur_flag)
{
	if (cur_flag->is_negative)
		return (max(cur_flag->width, num_len + 1));
	return (max(cur_flag->width, num_len));
}
