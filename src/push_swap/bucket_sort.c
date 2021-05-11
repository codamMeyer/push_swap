#include "bucket_sort.h"
#include <math.h>
#include <stdio.h>
t_bucket create_bucket(const int bucket_size, const int *sorted)
{
    const t_bucket new_bucket = {
        .missing_elements = bucket_size,
        .start_index = 0,
        .end_index = bucket_size - 1,
        .min_value = sorted[0],
        .max_value = sorted[bucket_size - 1],
    };

    return (new_bucket);
}

int get_bucket_size(const int num_elements) 
{
    (void)num_elements;
    return 1;
}

t_bucket get_next_bucket(const t_bucket bucket, const int bucket_size, const int *sorted)
{
    t_bucket new_bucket;

    new_bucket.missing_elements = bucket_size;
    new_bucket.start_index = bucket.start_index + bucket_size;
    new_bucket.end_index = bucket.end_index + bucket_size;
    new_bucket.min_value = sorted[new_bucket.start_index];
    new_bucket.max_value = sorted[new_bucket.end_index];

    return (new_bucket);
}

t_optional_index search_stack_top(t_stack *stack, t_bucket *bucket)
{
    const int stack_size = size(stack);
    const int half_stack = stack_size - ceil((double)stack_size / 2.0);
    t_optional_index element_index;
    int i;

    element_index.initialized = FALSE;
    i = stack->top;
    while (i >= half_stack)
    {
        if (stack->elements[i] >= bucket->min_value && stack->elements[i] <= bucket->max_value)
        {
            element_index.index = i;
            element_index.initialized = TRUE;
            return (element_index);
        }
        --i;
    }
    return (element_index);
}

t_optional_index search_stack_bottom(t_stack *stack, t_bucket *bucket)
{
    const int stack_size = size(stack);
    const int half_stack = floor((double)stack_size / 2.0);
    t_optional_index element_index;
    int i;

    element_index.initialized = FALSE;
    i = 0;
    while (i < half_stack)
    {
        if (stack->elements[i] >= bucket->min_value && stack->elements[i] <= bucket->max_value)
        {
            element_index.index = i;
            element_index.initialized = TRUE;
            return (element_index);
        }
        ++i;
    }
    return (element_index);
}

t_bool is_closer_to_top(t_stack *stack, int element_index) 
{
    (void)stack;
    (void)element_index;
    return 1;
}

int move_element_to_top(t_stack_pair *stacks, int counter, t_operation operation) 
{
    (void)stacks;
    (void)operation;
    (void)counter;
    return 1;
}

int bring_element_to_top(t_stack_pair *stacks, int element, t_write_instruction write_instruction) 
{
    (void)stacks;
    (void)element;
    (void)write_instruction;
    return 1;
}

int get_element_index(t_stack *stack, int element_index)
{
    (void)stack;
    (void)element_index;
    return 1;

}

int push_elements_back(t_stack_pair *stacks, t_write_instruction write_instruction) 
{
    (void)stacks;
    (void)write_instruction;
    return 1;

}

int bucket_sort(int elements_size,
				int *elements,
				t_write_instruction write_instruction) 
{
    (void) elements_size;
    (void) *elements;
	(void)write_instruction;
    return 1;

    //define n buckts based on size
    //get cur bucket start/end
    //search top part
    //serch bottom part
    //bring to top (fastest way) and move to b
    
    //search for elements in stack b (largest first) and push to a
}

