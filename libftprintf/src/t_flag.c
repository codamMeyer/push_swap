#include <inc/t_flag.h>

t_bool	is_right_justified(const t_flag *cur_flag, int size)
{
	return (cur_flag->width > 0 && cur_flag->width > size);
}

t_bool	is_left_justified(const t_flag *cur_flag, int size)
{
	return (cur_flag->left_align && \
			cur_flag->width > 0 && \
			cur_flag->width > size);
}

t_bool	needs_to_adjust_precision(const t_flag *cur_flag, int size)
{
	return (size < cur_flag->precision || cur_flag->precision == 0);
}

t_flag	create_flag_struct(void)
{
	t_flag	flag;

	flag.width = UNINITIALIZED;
	flag.precision = UNINITIALIZED;
	flag.left_align = FALSE;
	flag.is_negative = FALSE;
	flag.padding_char = ' ';
	flag.type = '%';
	return (flag);
}
