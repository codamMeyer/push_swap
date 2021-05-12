#ifndef BUCKET_H
# define BUCKET_H
# include <utils/defs.h>

typedef struct s_bucket
{
	int		missing_elements;
	int		min_value;
	int		max_value;
	int		start_index;
	int		end_index;
	t_bool	is_valid;
}	t_bucket;

t_bucket			create_bucket(int bucket_size, \
									const int *sorted);
t_bucket			get_next_bucket(t_bucket bucket, \
									int bucket_size, \
									const int *sorted, \
									int num_elements);
t_bool				is_part_of_bucket(const int element, \
									const t_bucket *bucket);

#endif