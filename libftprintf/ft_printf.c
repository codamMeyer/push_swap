#include <ft_printf.h>
#include <inc/ft_printf_helpers.h>
#include <inc/handle_char.h>
#include <inc/handle_hex.h>
#include <inc/handle_int.h>
#include <inc/handle_modifier.h>
#include <inc/handle_percent.h>
#include <inc/handle_str.h>
#include <inc/utils.h>
#include <libft/libft.h>

static int	handle_flag(const char **format,
							va_list args,
							t_flag *cur_flag)
{
	int	char_count;

	char_count = 0;
	cur_flag->type = *(*format);
	if ((cur_flag->type == 'd' || cur_flag->type == 'i'))
		char_count += handle_int(format, args, cur_flag);
	if (cur_flag->type == 'u')
		char_count += handle_unsigned(format, args, cur_flag);
	if (cur_flag->type == 'c')
		char_count += handle_char(format, args, cur_flag);
	if (cur_flag->type == 's')
		char_count += handle_string(format, args, cur_flag);
	if ((cur_flag->type == 'x' || cur_flag->type == 'X'))
		char_count += handle_hex(format, args, cur_flag->type == 'X', cur_flag);
	if (cur_flag->type == 'p')
		char_count += handle_ptr(format, args, cur_flag);
	return (char_count);
}

static int	handle_next_arg(va_list args, const char **format)
{
	t_flag	cur_flag;
	int		char_count;

	cur_flag = create_flag_struct();
	char_count = 0;
	while (is_valid(format))
	{
		if (is_modifier(*(*format)))
			handle_modifier(format, args, &cur_flag);
		if (is_flag(*(*format)))
			char_count += handle_flag(format, args, &cur_flag);
	}
	if (*(*format) == '%')
		char_count += handle_percent(format, &cur_flag);
	return (char_count);
}

static int	print_str_until_next_flag(const char **format)
{
	const int	num_char = find_char_index(*format);

	ft_putnstr_fd(*format, STDOUT_FILENO, num_char);
	*format += num_char;
	return (num_char);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		char_count;

	char_count = 0;
	va_start(args, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			++format;
			char_count += handle_next_arg(args, &format);
		}
		char_count += print_str_until_next_flag(&format);
	}
	va_end(args);
	return (char_count);
}
