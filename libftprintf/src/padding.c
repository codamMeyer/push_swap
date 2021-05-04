#include <inc/padding.h>
#include <libft/libft.h>
#include <stdio.h>

void	insert_left_padding(t_flag *cur_flag, int len, const char *src)
{
	if ((cur_flag->precision != UNINITIALIZED && cur_flag->type != 's'))
		cur_flag->padding_char = ' ';
	if (cur_flag->is_negative && cur_flag->padding_char == '0')
	{
		ft_putchar_fd('-', STDOUT_FILENO);
		cur_flag->width -= 1;
	}
	if (cur_flag->is_negative && cur_flag->padding_char == ' ')
	{
		insert_padding(cur_flag->padding_char, (cur_flag->width - 1) - len);
		ft_putchar_fd('-', STDOUT_FILENO);
	}
	else
		insert_padding(cur_flag->padding_char, cur_flag->width - len);
	if (len > 1)
		ft_putnstr_fd(src, STDOUT_FILENO, len);
	else if (len > 0)
		ft_putchar_fd(*src, STDOUT_FILENO);
}

void	insert_right_padding(t_flag *cur_flag, int len, const char *src)
{
	if (cur_flag->is_negative)
	{
		ft_putchar_fd('-', STDOUT_FILENO);
		cur_flag->width -= 1;
	}
	if (len > 1)
		ft_putnstr_fd(src, STDOUT_FILENO, len);
	else if (len > 0)
		ft_putchar_fd(*src, STDOUT_FILENO);
	insert_padding(cur_flag->padding_char, cur_flag->width - len);
}

void	insert_padding(char c, int n)
{
	while (n > 0)
	{
		ft_putchar_fd(c, STDOUT_FILENO);
		--n;
	}
}
