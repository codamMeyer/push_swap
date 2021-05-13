#ifndef UTILS_H
# define UTILS_H
# include <utils/defs.h>

typedef void(*t_write_instruction)(	const char 		*str, int n);

void	swap_elements(int *cur, int *prev);
void	print_instruction(const char *instruction, int times);
t_bool	is_descending_order(int num_elements, const int *elements);
int		*sort_elements(int num_elements, const int *elements);

#endif