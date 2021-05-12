#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <utils/status.h>
# include <utils/defs.h>

t_bool      is_list_sorted(int num_elements, const int *elements);
t_status	run_push_swap(int num_elements, const char *elements[]);

#endif