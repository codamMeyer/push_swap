#include <inc/defs.h>
#include <inc/handle_percent.h>
#include <inc/padding.h>
#include <inc/utils.h>
#include <libft/libft.h>

static void	insert_percent_padding(t_flag *cur_flag, char chr)
{
	if (is_left_justified(cur_flag, 1))
		insert_right_padding(cur_flag, 1, &chr);
	else if (is_right_justified(cur_flag, 1))
		insert_left_padding(cur_flag, 1, &chr);
	else
		ft_putchar_fd(chr, STDOUT_FILENO);
}

int	handle_percent(const char **format, t_flag *cur_flag)
{
	const char	prev = *(*format - 1);
	const char	chr = '%';

	if (prev == '%' || !is_flag(prev))
	{
		insert_percent_padding(cur_flag, chr);
		++(*format);
		if (cur_flag->width != UNINITIALIZED && cur_flag->width != 0)
			return (cur_flag->width);
		return (1);
	}
	return (0);
}
