#include <inc/handle_char.h>
#include <inc/padding.h>
#include <libft/libft.h>
#include <unistd.h>

static void	insert_char_padding(t_flag *cur_flag, char chr)
{
	if (is_left_justified(cur_flag, 1))
		insert_right_padding(cur_flag, 1, &chr);
	else if (is_right_justified(cur_flag, 1))
		insert_left_padding(cur_flag, 1, &chr);
	else
		ft_putchar_fd(chr, STDOUT_FILENO);
}

int	handle_char(const char **format,
							va_list args,
							t_flag *cur_flag)
{
	const char	chr = (char)va_arg(args, int);

	insert_char_padding(cur_flag, chr);
	++(*format);
	if (cur_flag->width != UNINITIALIZED && cur_flag->width != 0)
		return (cur_flag->width);
	return (1);
}
