#ifndef UTILS_H
# define UTILS_H
# include <inc/defs.h>
# include <inc/t_flag.h>
# include <stdarg.h>

int		get_width(const char **format, va_list args);
int		get_precision(const char **format, va_list args);
char	*adjust_precision(char *num, int *num_len, t_flag *cur_flag);
t_bool	is_modifier(char cur);
t_bool	is_flag(char cur);

#endif
