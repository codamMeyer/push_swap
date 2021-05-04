#include <inc/handle_str.h>
#include <inc/math.h>
#include <inc/padding.h>
#include <libft/libft.h>

static int	print_null(t_flag *cur_flag, char *to_print)
{
	int		len;

	len = ft_strlen(to_print);
	if (cur_flag->precision < len && cur_flag->precision != UNINITIALIZED)
		len = cur_flag->precision;
	if (is_left_justified(cur_flag, len))
		insert_right_padding(cur_flag, len, to_print);
	else if (is_right_justified(cur_flag, len))
		insert_left_padding(cur_flag, len, to_print);
	else
		ft_putnstr_fd(to_print, STDOUT_FILENO, len);
	return (len);
}

static int	define_len(const char *str, t_flag *cur_flag)
{
	int		len;

	len = ft_strlen(str);
	if (cur_flag->precision != UNINITIALIZED)
	{
		if (cur_flag->precision < len)
			len = cur_flag->precision;
	}
	return (len);
}

static	void	insert_str_padding(t_flag *cur_flag, int len, const char *str)
{
	if (is_left_justified(cur_flag, len))
		insert_right_padding(cur_flag, len, str);
	else if (is_right_justified(cur_flag, len))
		insert_left_padding(cur_flag, len, str);
	else
		ft_putnstr_fd(str, STDOUT_FILENO, len);
}

int	handle_string(const char **format,
								va_list args,
								t_flag *cur_flag)
{
	const char	*str = va_arg(args, char *);
	int			len;

	if (!str)
	{
		++(*format);
		return (max(print_null(cur_flag, "(null)"), cur_flag->width));
	}
	len = define_len(str, cur_flag);
	insert_str_padding(cur_flag, len, str);
	++(*format);
	return (max(cur_flag->width, len));
}
