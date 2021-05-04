#ifndef PADDING_H
# define PADDING_H
# include <inc/t_flag.h>

void	insert_left_padding(t_flag *cur_flag, int len, const char *src);
void	insert_right_padding(t_flag *cur_flag, int len, const char *src);
void	insert_padding (char c, int n);

#endif
