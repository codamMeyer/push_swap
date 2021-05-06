#ifndef UTILS_H
# define UTILS_H
# include <utils/defs.h>
# define STR_SA "sa"
# define STR_SB "sb"
# define STR_SS "ss"
# define STR_PA "pa"
# define STR_PB "pb"
# define STR_RA "ra"
# define STR_RB "rb"
# define STR_RR "rr"
# define STR_RRA "rra"
# define STR_RRB "rrb"
# define STR_RRR "rrr"
# define NOT_FOUND -1
# include <stack/processor.h>

typedef void(*t_operation)(t_stack_pair			 	*stack);
typedef void(*t_write_instruction)(	const char 		*str, int n);

void	swap_elements(int *cur, int *prev);
void	print_instruction(const char *instruction, int times);
t_bool	is_list_sorted(int elements_size, int *elements);
t_bool	is_descending_order(int elements_size, int *elements);
int		*sort_elements(int elements_size, int *elements);

#endif