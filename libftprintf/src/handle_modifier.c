#include <inc/handle_modifier.h>
#include <inc/utils.h>
#include <libft/libft.h>

static void	set_precision(const char **format,
							char *cur,
							t_flag *cur_flag,
							va_list args)
{
	++(*format);
	cur_flag->precision = get_precision(format, args);
	if (cur_flag->precision < 0)
		cur_flag->precision = UNINITIALIZED;
	*cur = *(*format);
}

static void	set_width(const char **format,
						char *cur,
						t_flag *cur_flag,
						va_list args)
{
	cur_flag->width = get_width(format, args);
	if (cur_flag->width < 0)
	{
		cur_flag->width *= -1;
		cur_flag->padding_char = ' ';
		cur_flag->left_align = TRUE;
	}
	*cur = *(*format);
}

static void	set_left_alignment(const char **format,
									char *cur,
									t_flag *cur_flag)
{
	cur_flag->padding_char = ' ';
	cur_flag->left_align = TRUE;
	++(*format);
	*cur = *(*format);
}

static void	get_width_and_set_padding_char(const char **format,
									char *cur,
									t_flag *cur_flag,
									va_list args)
{
	const char	prev = *(*format - 1);

	if (prev == '-')
		return ;
	cur_flag->padding_char = '0';
	++(*format);
	set_width(format, cur, cur_flag, args);
}

void	handle_modifier(const char **format,
							va_list args,
							t_flag *cur_flag)
{
	char	cur;

	cur = *(*format);
	while (is_modifier(cur))
	{
		if (cur == '0')
			get_width_and_set_padding_char(format, &cur, cur_flag, args);
		if (cur == '-')
			set_left_alignment(format, &cur, cur_flag);
		if (cur == '.')
			set_precision(format, &cur, cur_flag, args);
		if (ft_isdigit(cur) || cur == '*')
			set_width(format, &cur, cur_flag, args);
	}
}
