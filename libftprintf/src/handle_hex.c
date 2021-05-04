#include <inc/handle_hex.h>
#include <inc/int_to_hex.h>
#include <inc/math.h>
#include <inc/padding.h>
#include <inc/utils.h>
#include <libft/libft.h>

static void	copy_address(char *str, t_bool with_prefix)
{
	if (with_prefix)
		ft_putstr_fd("0x", STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
}

static void	insert_hex_padding(t_flag *cur_flag, int num_len, char *num_str)
{
	if (is_left_justified(cur_flag, num_len))
		insert_right_padding(cur_flag, num_len, num_str);
	else if (is_right_justified(cur_flag, num_len))
		insert_left_padding(cur_flag, num_len, num_str);
	else if (num_len > 0)
		copy_address(num_str, FALSE);
}

static void	insert_ptr_padding(t_flag *cur_flag,
									int address_len,
									char *address_str)
{
	if (is_left_justified(cur_flag, address_len))
	{
		copy_address(address_str, TRUE);
		insert_padding(cur_flag->padding_char, \
						cur_flag->width - (address_len + 2));
	}
	else if (is_right_justified(cur_flag, address_len + 2))
	{
		insert_padding(cur_flag->padding_char, \
						cur_flag->width - (address_len + 2));
		copy_address(address_str, TRUE);
	}
	else
		copy_address(address_str, TRUE);
}

int	handle_hex(const char **format,
				va_list args,
				t_bool upper,
				t_flag *cur_flag)
{
	const int	nbr = va_arg(args, int);
	char		*num_str;
	int			num_len;

	num_str = int_to_hex(nbr, upper);
	if (cur_flag->precision == 0 && nbr == 0)
		num_len = 0;
	else
		num_len = ft_strlen(num_str);
	if (needs_to_adjust_precision(cur_flag, num_len))
		num_str = adjust_precision(num_str, &num_len, cur_flag);
	insert_hex_padding(cur_flag, num_len, num_str);
	++(*format);
	free(num_str);
	return (max(cur_flag->width, num_len));
}

int	handle_ptr(const char **format,
				va_list args,
				t_flag *cur_flag)
{
	const char		*ptr = va_arg(args, void *);
	const long int	address = (long int)&(*ptr);
	char			*address_str;
	int				address_len;

	if (!ptr)
		cur_flag->precision = max(cur_flag->precision, 1);
	address_str = ulong_int_to_hex(address, 0);
	address_len = ft_strlen(address_str);
	if (address_len < cur_flag->precision)
		address_str = adjust_precision(address_str, &address_len, cur_flag);
	insert_ptr_padding(cur_flag, address_len, address_str);
	++(*format);
	free(address_str);
	return (max(cur_flag->width, address_len + 2));
}
