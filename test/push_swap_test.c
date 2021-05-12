#include "ctest.h"
#include <push_swap/insertion_sort.h>
#include <push_swap/bucket_sort.h>
#include <push_swap/special_cases_sort.h>
#include <parser/parse_instructions.h>
#include <push_swap/push_swap.h>
#include <utils/status.h>
#include <stack/stack_utils.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

t_bool is_stack_sorted_ascending(const t_stack *stack)
{
    return (is_sorted(stack, is_ascending));
}

////////////////////////////////////////////
//           run_push_swap_test           //
////////////////////////////////////////////

CTEST(run_push_swap_test, empty_string)
{
    const char *argv[] = {""};
    ASSERT_EQUAL(ERROR, run_push_swap(1, argv));
}

////////////////////////////////////////////
//      sort_descending_order_test        //
////////////////////////////////////////////

void	insert_instructions_to_reverse_order(const char *instruction, int times)
{
    const t_instructions solution[10] = {RRA, PB, RRA, PB, RRA, PB, SA, PA, PA, PA};
    static int instruction_index = 0;
	int i = 0;
	while (i < times)
	{
        t_instructions cur = get_instruction(instruction);
        ASSERT_EQUAL(solution[instruction_index++], cur);
        ++i;
	}
}

CTEST(sort_descending_order_test, five_sorted_descending_order)
{
    ASSERT_EQUAL(10, from_descending_to_ascending_order(5, insert_instructions_to_reverse_order));
}


CTEST(sort_descending_order_test, one_element)
{
    ASSERT_EQUAL(0, from_descending_to_ascending_order(1, insert_instructions_to_reverse_order));
}


////////////////////////////////////////////
//           inertion_sort_test           //
////////////////////////////////////////////

CTEST_DATA(sort_elements_test)
{
	int *sorted;
};

CTEST_SETUP(sort_elements_test)
{
	data->sorted = NULL;
}

CTEST_TEARDOWN(sort_elements_test)
{
	free(data->sorted);
}

CTEST2(sort_elements_test, five_elements)
{
    const int size = 7;
	int elements[] = {5, 3, 4, 1, 2, 10, 9};
    data->sorted = sort_elements(size, elements);
    ASSERT_TRUE(is_list_sorted(size, data->sorted));
}

CTEST_DATA(find_element_index_test)
{
    int elements[5];
    t_stack _stack;
    t_stack *stack;
};

CTEST_SETUP(find_element_index_test)
{
    data->stack = &(data->_stack);
    data->stack->elements = (int *)data->elements;
    data->stack->top = -1;
    push(data->stack, 5);
    push(data->stack, 4);
    push(data->stack, 8);
    push(data->stack, 1);
    push(data->stack, 0);
}

CTEST_TEARDOWN(find_element_index_test)
{
    (void)data;
}

CTEST2(find_element_index_test, element_8_index_2)
{
    const int to_find = 8;
    ASSERT_EQUAL(2, find_element_index(data->stack, to_find).index);
}

CTEST2(find_element_index_test, not_in_stack)
{
    const int to_find = 7;
    ASSERT_FALSE(find_element_index(data->stack, to_find).initialized);
}


CTEST_DATA(move_element_to_b_test)
{
    int elements_a[5];
    int elements_b[5];
    t_stack_pair _stacks;
    t_stack_pair *stacks;
};

CTEST_SETUP(move_element_to_b_test)
{
    data->stacks = &(data->_stacks);
    data->stacks->a.elements = (int *)data->elements_a;
    data->stacks->a.top = -1;
    data->stacks->b.elements = (int *)data->elements_b;
    data->stacks->b.top = -1;
    push(&data->stacks->a, 5);
    push(&data->stacks->a, 4);
    push(&data->stacks->a, 8);
    push(&data->stacks->a, 1);
    push(&data->stacks->a, 0);
}

CTEST_TEARDOWN(move_element_to_b_test)
{
    (void)data;
}


void write_inst(const char *instruction, int i)
{
    while (i > 0)
    {
        printf("%s, ", instruction);
        --i;
    }
}

CTEST2(move_element_to_b_test, element_8_index_2)
{
    const int element = 8;
    ASSERT_EQUAL(0, size(&(data->stacks->b)));
    ASSERT_EQUAL(5, size(&(data->stacks->a)));
    move_element_to_stack_b(data->stacks, element, write_inst);
    ASSERT_EQUAL(1, size(&(data->stacks->b)));
    ASSERT_EQUAL(4, size(&(data->stacks->a)));
    ASSERT_EQUAL(element, data->stacks->b.elements[data->stacks->b.top]);
}

CTEST2(move_element_to_b_test, element_0_at_top)
{
    const int element = 0;
    ASSERT_EQUAL(0, size(&(data->stacks->b)));
    ASSERT_EQUAL(5, size(&(data->stacks->a)));
    move_element_to_stack_b(data->stacks, element, write_inst);
    ASSERT_EQUAL(1, size(&(data->stacks->b)));
    ASSERT_EQUAL(4, size(&(data->stacks->a)));
    ASSERT_EQUAL(element, data->stacks->b.elements[data->stacks->b.top]);
}

CTEST2(move_element_to_b_test, element_closer_to_bottom)
{
    const int element = 4;
    ASSERT_EQUAL(0, size(&(data->stacks->b)));
    ASSERT_EQUAL(5, size(&(data->stacks->a)));
    move_element_to_stack_b(data->stacks, element, write_inst);
    ASSERT_EQUAL(1, size(&(data->stacks->b)));
    ASSERT_EQUAL(4, size(&(data->stacks->a)));
    ASSERT_EQUAL(element, data->stacks->b.elements[data->stacks->b.top]);
}

CTEST2(move_element_to_b_test, element_at_bottom)
{
    const int element = 5;
    ASSERT_EQUAL(0, size(&(data->stacks->b)));
    ASSERT_EQUAL(5, size(&(data->stacks->a)));
    move_element_to_stack_b(data->stacks, element, write_inst);
    ASSERT_EQUAL(1, size(&(data->stacks->b)));
    ASSERT_EQUAL(4, size(&(data->stacks->a)));
    ASSERT_EQUAL(element, data->stacks->b.elements[data->stacks->b.top]);
}

CTEST2(move_element_to_b_test, stack_a_with_3_elements_b_with_2)
{
    pb(data->stacks);
    pb(data->stacks);
    const int element = 5;
    ASSERT_EQUAL(2, size(&(data->stacks->b)));
    ASSERT_EQUAL(3, size(&(data->stacks->a)));
    move_element_to_stack_b(data->stacks, element, write_inst);
    ASSERT_EQUAL(3, size(&(data->stacks->b)));
    ASSERT_EQUAL(2, size(&(data->stacks->a)));
    ASSERT_EQUAL(element, data->stacks->b.elements[data->stacks->b.top]);
}

CTEST(insertion_sort_test, insertion_sort_test_1)
{
    int elements[] = {5, 4, 8, 1, 9};
    insertion_sort(5, elements, write_inst);
}

CTEST(insertion_sort_test, test_5)
{
    int elements[] = {5, 1, 2, 4, 3};
    insertion_sort(5, elements, write_inst);
}


////////////////////////////////////////////
//             bucket_sort_test           //
////////////////////////////////////////////


CTEST_DATA(small_bucket_sort_test)
{
    int elements_a[20];
    int elements_b[20];
    int *sorted;
    t_stack_pair _stacks;
    t_stack_pair *stacks;
};

CTEST_SETUP(small_bucket_sort_test)
{
    data->stacks = &(data->_stacks);
    data->stacks->a.elements = (int *)data->elements_a;
    data->stacks->a.top = -1;
    data->stacks->b.elements = (int *)data->elements_b;
    data->stacks->b.top = -1;
    push(&data->stacks->a, 5);
    push(&data->stacks->a, 4);
    push(&data->stacks->a, 0);
    push(&data->stacks->a, 1);
    push(&data->stacks->a, 2);
    push(&data->stacks->a, 3);
    push(&data->stacks->a, 8);
    push(&data->stacks->a, 7);
    push(&data->stacks->a, 9);
    push(&data->stacks->a, 6);
    push(&data->stacks->a, 11);
    push(&data->stacks->a, 18);
    push(&data->stacks->a, 12);
    push(&data->stacks->a, 14);
    push(&data->stacks->a, 13);
    push(&data->stacks->a, 15);
    push(&data->stacks->a, 16);
    push(&data->stacks->a, 17);
    push(&data->stacks->a, 19);
    push(&data->stacks->a, 10);

    data->sorted = sort_elements(20, data->elements_a);
}


CTEST_TEARDOWN(small_bucket_sort_test)
{
    (void)data;
    free(data->sorted);
}

CTEST2(small_bucket_sort_test, no_element_from_bucket_at_top)
{
    t_bucket bucket = create_bucket(5, data->sorted);
    t_optional_index element = search_stack_top(&(data->stacks->a),&bucket);
    ASSERT_FALSE(element.initialized);
}

CTEST2(small_bucket_sort_test, find_element_from_bucket_at_top)
{
    reverse_rotate(&(data->stacks->a));
    reverse_rotate(&(data->stacks->a));
    t_bucket bucket = create_bucket(5, data->sorted);
    t_optional_index element = search_stack_top(&(data->stacks->a),&bucket);
    ASSERT_TRUE(element.initialized);
    ASSERT_EQUAL(19, element.index);
}

CTEST2(small_bucket_sort_test, no_element_from_bucket_at_bottom)
{
    t_bucket bucket = create_bucket(5, data->sorted);
    bucket = get_next_bucket(bucket, 5, data->sorted, 20);
    bucket = get_next_bucket(bucket, 5, data->sorted, 20);
    bucket = get_next_bucket(bucket, 5, data->sorted, 20);
    t_optional_index element = search_stack_bottom(&(data->stacks->a),&bucket);
    ASSERT_FALSE(element.initialized);
}

CTEST2(small_bucket_sort_test, find_element_from_bucket_at_bottom)
{
    t_bucket bucket = create_bucket(5, data->sorted);
    t_optional_index element = search_stack_bottom(&(data->stacks->a),&bucket);
    ASSERT_TRUE(element.initialized);
    ASSERT_EQUAL(1, element.index);
}

CTEST(small_bucket_sort_test, create_bucket_test)
{
    const int sorted[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    const int bucket_size = 5;
    t_bucket bucket = create_bucket(bucket_size, sorted);
    ASSERT_EQUAL(0, bucket.start_index);
    ASSERT_EQUAL(4, bucket.end_index);
    ASSERT_EQUAL(bucket_size, bucket.missing_elements);
    ASSERT_EQUAL(1, bucket.min_value);
    ASSERT_EQUAL(5, bucket.max_value);
}

CTEST(small_bucket_sort_test, get_next_bucket_test)
{
    const int sorted[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    const int bucket_size = 5;
    t_bucket bucket = create_bucket(bucket_size, sorted);
    
    bucket = get_next_bucket(bucket, bucket_size, sorted, 15);
    ASSERT_EQUAL(5, bucket.start_index);
    ASSERT_EQUAL(9, bucket.end_index);
    ASSERT_EQUAL(6, bucket.min_value);
    ASSERT_EQUAL(10, bucket.max_value);
    ASSERT_EQUAL(bucket_size, bucket.missing_elements);

    bucket = get_next_bucket(bucket, bucket_size, sorted, 15);
    ASSERT_EQUAL(10, bucket.start_index);
    ASSERT_EQUAL(14, bucket.end_index);
    ASSERT_EQUAL(11, bucket.min_value);
    ASSERT_EQUAL(15, bucket.max_value);
    ASSERT_EQUAL(bucket_size, bucket.missing_elements);
 }

CTEST_DATA(find_middle_element)
{
    int elements_a[5];
    int elements_b[4];
    int *sorted;
    t_stack_pair _stacks;
    t_stack_pair *stacks;
};

CTEST_SETUP(find_middle_element)
{
    data->stacks = &(data->_stacks);
    data->stacks->a.elements = (int *)data->elements_a;
    data->stacks->a.top = -1;
    data->stacks->b.elements = (int *)data->elements_b;
    data->stacks->b.top = -1;
    push(&data->stacks->a, 2);
    push(&data->stacks->a, 4);
    push(&data->stacks->a, 1);
    push(&data->stacks->a, 3);
    push(&data->stacks->a, 5);

    push(&data->stacks->b, 5);
    push(&data->stacks->b, 4);
    push(&data->stacks->b, 1);
    push(&data->stacks->b, 3);
    push(&data->stacks->b, 2);
}

CTEST_TEARDOWN(find_middle_element)
{
    (void)data;
    free(data->sorted);
}

CTEST2(find_middle_element, from_top)
{
    data->sorted = sort_elements(5, data->elements_a);
    t_bucket bucket = create_bucket(2, data->sorted);
    t_optional_index element = search_stack_top(&(data->stacks->a),&bucket);
    ASSERT_TRUE(element.initialized);
    ASSERT_EQUAL(2, element.index);
}

CTEST2(find_middle_element, from_bottom)
{
    data->sorted = sort_elements(5, data->elements_b);
    t_bucket bucket = create_bucket(2, data->sorted);
    t_optional_index element = search_stack_bottom(&(data->stacks->b),&bucket);
    ASSERT_FALSE(element.initialized);
}

CTEST(a, test)
{
    int elements[] = {19, 78, 47, 86, 53, 54, 38, 84, 94, 61, 29, 5, 68, 50, 3, 88, 66, 77, 26, 7, 30, 56, 92, 90, 83, 10, 87, 97, 17, 65, 55, 2, 9, 51, 20, 32, 48, 75, 71, 52, 14, 39, 74, 93, 46, 18, 11, 99, 96, 22, 70, 0, 33, 36, 73, 25, 72, 95, 13, 49, 69, 24, 37, 80, 45, 89, 8, 85, 58, 12, 43, 35, 34, 31, 1, 59, 41, 28, 82, 63, 6, 91, 57, 64, 62, 16, 40, 15, 27, 60, 76, 98, 4, 79, 23, 67, 44, 42, 81, 21};
    bucket_sort(100, elements, write_inst);
}
