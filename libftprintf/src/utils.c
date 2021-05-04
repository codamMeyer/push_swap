#include <inc/utils.h>
#include <libft/libft.h>

int	get_width(const char **format, va_list args)
{
	int		width;
	char	cur;

	width = 0;
	cur = *(*format);
	if (cur == '*')
	{
		++(*format);
		return (va_arg(args, int));
	}
	while (ft_isdigit(cur))
	{
		width = (width * 10) + (cur - '0');
		++(*format);
		cur = *(*format);
	}
	return (width);
}

int	get_precision(const char **format, va_list args)
{
	int		precision;
	char	cur;

	precision = 0;
	cur = *(*format);
	if (cur == '*')
	{
		++(*format);
		return (va_arg(args, int));
	}
	while (ft_isdigit(cur))
	{
		precision = (precision * 10) + (cur - '0');
		++(*format);
		cur = *(*format);
	}
	return (precision);
}

char	*adjust_precision(char *num, int *num_len, t_flag *cur_flag)
{
	char	*num_prec;

	if (cur_flag->precision != 0)
	{
		num_prec = ft_calloc(cur_flag->precision + 1, sizeof(char));
		ft_memset(num_prec, '0', cur_flag->precision - *num_len);
		ft_strcpy(num_prec + cur_flag->precision - *num_len, num);
		free(num);
		*num_len = ft_strlen(num_prec);
		return (num_prec);
	}
	return (num);
}

t_bool	is_modifier(char cur)
{
	return (ft_isdigit(cur) || \
			cur == '.' || \
			cur == '-' || \
			cur == '*');
}

t_bool	is_flag(char cur)
{
	return (cur == 'd' || \
			cur == 'i' || \
			cur == 'u' || \
			cur == 'x' || \
			cur == 'X' || \
			cur == 's' || \
			cur == 'p' || \
			cur == 'c');
}
