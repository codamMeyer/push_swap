#ifndef HANDLE_INT_H
# define HANDLE_INT_H
# include <stdarg.h>
# include <inc/t_flag.h>

int	handle_int(const char **format, va_list args, t_flag *cur_flag);
int	handle_unsigned(const char **format, va_list args, t_flag *cur_flag);

#endif
