#include <inc/handle_int.h>
#include <inc/handle_int_helpers.h>
#include <inc/math.h>
#include <inc/padding.h>
#include <inc/utils.h>
#include <libft/libft.h>

static void	copy_number(char *num,
						t_flag *cur_flag)
{
	if (cur_flag->is_negative)
		ft_putchar_fd('-', STDOUT_FILENO);
	ft_putstr_fd(num, STDOUT_FILENO);
}

static void	insert_number_padding(t_flag *cur_flag,
										int num_len,
										char *num_str)
{
	if (is_left_justified(cur_flag, num_len))
		insert_right_padding(cur_flag, num_len, num_str);
	else if (is_right_justified(cur_flag, num_len))
		insert_left_padding(cur_flag, num_len, num_str);
	else if (num_len > 0)
		copy_number(num_str, cur_flag);
}

int	handle_int(const char **format,
				va_list args,
				t_flag *cur_flag)
{
	int		n;
	char	*num_str;
	int		num_len;
	int		char_count;

	n = va_arg(args, int);
	check_if_negative(&n, cur_flag);
	num_str = ft_itoa(n);
	num_len = calculate_num_len(n, num_str, cur_flag);
	if (needs_to_adjust_precision(cur_flag, num_len))
		num_str = adjust_precision(num_str, &num_len, cur_flag);
	char_count = calculate_char_count(num_len, cur_flag);
	insert_number_padding(cur_flag, num_len, num_str);
	++(*format);
	free(num_str);
	return (char_count);
}

int	handle_unsigned(const char **format,
					va_list args,
					t_flag *cur_flag)
{
	int		n;
	char	*num_str;
	int		num_len;

	n = va_arg(args, unsigned int);
	num_str = unsigned_to_string(n);
	num_len = calculate_num_len(n, num_str, cur_flag);
	if (needs_to_adjust_precision(cur_flag, num_len))
		num_str = adjust_precision(num_str, &num_len, cur_flag);
	insert_number_padding(cur_flag, num_len, num_str);
	++(*format);
	free(num_str);
	return (max(cur_flag->width, num_len));
}
