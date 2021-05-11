#ifndef BUCKET_SORT_H
# define BUCKET_SORT_H
# include "utils.h"

typedef struct s_bucket
{
    int missing_elements;
    int min_value;
    int max_value;
    int start_index;
    int end_index;
} t_bucket;

typedef struct s_optional_index
{
	int		index;
	t_bool	initialized;
}	t_optional_index;

t_bucket        create_bucket(const int bucket_size, const int *sorted);
int             get_bucket_size(const int num_elements);
t_bucket        get_next_bucket(const t_bucket bucket, const int bucket_size, const int *sorted);
t_optional_index  search_stack_top(t_stack *stack, t_bucket *bucket);
t_optional_index  search_stack_bottom(t_stack *stack, t_bucket *bucket);
t_bool          is_closer_to_top(t_stack *stack, int element_index);
int             move_element_to_top(t_stack_pair *stacks, int counter, t_operation operation);
int             get_element_index(t_stack *stack, int element_index);
int             push_elements_back(t_stack_pair *stacks, t_write_instruction write_instruction);
int             bucket_sort(int num_elements,int *elements,t_write_instruction write_instruction);

#endif