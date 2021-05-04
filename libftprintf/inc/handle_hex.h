#ifndef HANDLE_HEX_H
# define HANDLE_HEX_H
# include <inc/defs.h>
# include <inc/t_flag.h>
# include <stdarg.h>

int	handle_hex(const char **format, \
				va_list args, \
				t_bool upper, \
				t_flag *cur_flag);
int	handle_ptr(const char **format, va_list args, t_flag *cur_flag);

#endif
