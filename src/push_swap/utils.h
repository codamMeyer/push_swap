#ifndef UTILS_H
# define UTILS_H
# include <utils/defs.h>
# define STR_SA "sa\n"
# define STR_SB "sb\n"
# define STR_SS "ss\n"
# define STR_PA "pa\n"
# define STR_PB "pb\n"
# define STR_RA "ra\n"
# define STR_RB "rb\n"
# define STR_RR "rr\n"
# define STR_RRA "rra\n"
# define STR_RRB "rrb\n"
# define STR_RRR "rrr\n"

typedef void(*t_write_instruction)(const char *, int);

void	swap_elements(int *cur, int *prev);
void	print_instruction(const char *instruction, int times);
t_bool	is_list_sorted(int elements_size, int *elements);
t_bool	is_descending_order(int elements_size, int *elements);

#endif