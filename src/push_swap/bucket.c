#include "bucket.h"


t_bucket	create_bucket(int bucket_size, const int *sorted)
{
	const t_bucket	new_bucket = {
		.missing_elements = bucket_size,
		.start_index = 0,
		.end_index = bucket_size - 1,
		.min_value = sorted[0],
		.max_value = sorted[bucket_size - 1],
		.is_valid = TRUE,
	};

	return (new_bucket);
}

t_bucket	get_next_bucket(t_bucket bucket,
							int bucket_size,
							const int *sorted,
							int num_elements)
{
	t_bucket	new_bucket;

	new_bucket.missing_elements = bucket_size;
	new_bucket.start_index = bucket.start_index + bucket_size;
	new_bucket.end_index = bucket.end_index + bucket_size;
	new_bucket.is_valid = FALSE;
	if (new_bucket.end_index < num_elements)
	{
		new_bucket.min_value = sorted[new_bucket.start_index];
		new_bucket.max_value = sorted[new_bucket.end_index];
		new_bucket.is_valid = TRUE;
	}
	return (new_bucket);
}

t_bool	is_part_of_bucket(const int element, const t_bucket *bucket)
{
	return (element >= bucket->min_value && element <= bucket->max_value);
}
