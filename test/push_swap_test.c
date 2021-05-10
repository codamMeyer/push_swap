#include "ctest.h"
#include <push_swap/bubble_sort.h>
#include <push_swap/merge_sort.h>
#include <push_swap/insertion_sort.h>
#include <push_swap/special_cases_sort.h>
#include <parser/parse_instructions.h>
#include <push_swap/push_swap.h>
#include <utils/status.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



typedef t_bool (*t_compare)(int, int);

t_bool is_ascending(int top, int bottom)
{
    return (top < bottom);
}

t_bool is_descending(int top, int bottom)
{
    return (top > bottom);
}

t_bool is_stack_sorted_test(const t_stack *stack, t_compare compare)
{
	const int	stack_size = size(stack);
	int			i;

	i = 1;
	while (i < stack_size)
	{
		if (!compare(stack->elements[i], stack->elements[i - 1]))
		{
			return (FALSE);
		}
		++i;
	}
	return (TRUE);
}

t_bool is_stack_sorted_ascending(const t_stack *stack)
{
    return (is_stack_sorted_test(stack, is_ascending));
}

t_bool is_stack_sorted_descending(const t_stack *stack)
{
    return (is_stack_sorted_test(stack, is_descending));
}

////////////////////////////////////////////
//           run_push_swap_test           //
////////////////////////////////////////////

CTEST(run_push_swap_test, empty_string)
{
    const char *argv[] = {""};
    ASSERT_EQUAL(ERROR, run_push_swap(1, argv));
}

//////////////////////////////////////////////
//       	    bubble_sort_test            //
//////////////////////////////////////////////

void	insert_instruction_no_call(const char *instruction, int times)
{
    (void)instruction;
    (void)times;
    ASSERT_TRUE(0);
}

CTEST(bubble_sort_test, one_element)
{
	int elements[1] = {1};
    ASSERT_EQUAL(0, bubble_sort(1, elements, insert_instruction_no_call));
}

CTEST(bubble_sort_test, two_sorted_elements)
{
	int elements[2] = {1, 2};
    ASSERT_EQUAL(0, bubble_sort(2, elements, insert_instruction_no_call));
}

CTEST(bubble_sort_test,five_sorted_elements)
{
	int elements[5] = {1, 2, 6, 9, 300};
    ASSERT_EQUAL(0, bubble_sort(5, elements, insert_instruction_no_call));
}

void	insert_instruction_3_unsorted_elements(const char *instruction, int times)
{
    const t_instructions solution[15] = {PB, PB, SB, PB, SB, PA, PA, PA, PB, PB, SB, PB, PA, PA, PA};
    static int instruction_index = 0;
	int i = 0;
	while (i < times)
	{
        t_instructions cur = get_instruction(instruction);
        ASSERT_EQUAL(solution[instruction_index++], cur);
        ++i;
	}
}

CTEST(bubble_sort_test, three_unsorted_elements_47_total)
{
	int elements[3] = {300, 6, 2};
    ASSERT_EQUAL(15, bubble_sort(3, elements, insert_instruction_3_unsorted_elements));
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
    ASSERT_EQUAL(2, find_element_index(data->stack, to_find));
}

CTEST2(find_element_index_test, not_in_stack)
{
    const int to_find = 7;
    ASSERT_EQUAL(NOT_FOUND, find_element_index(data->stack, to_find));
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
//      sort_ascending_stack_b_test       //
////////////////////////////////////////////

CTEST_DATA(sort_ascending_stack_b_test)
{
    int elements_a[5];
    int elements_b[5];
    t_stack_pair _stacks;
    t_stack_pair *stacks;
};

CTEST_SETUP(sort_ascending_stack_b_test)
{
    data->stacks = &(data->_stacks);
    data->stacks->a.elements = (int *)data->elements_a;
    data->stacks->a.top = -1;
    data->stacks->b.elements = (int *)data->elements_b;
    data->stacks->b.top = -1;
    push(&data->stacks->a, 5);
    push(&data->stacks->a, 4);
    push(&data->stacks->a, 8);
}

CTEST_TEARDOWN(sort_ascending_stack_b_test)
{
    (void)data;
}

CTEST2(sort_ascending_stack_b_test, empty_stack_b)
{
    insert_element(data->stacks, write_inst);
    ASSERT_TRUE(is_stack_sorted_descending(&data->stacks->b));
}

CTEST2(sort_ascending_stack_b_test, stack_b_size_one_element_bigger_than_top_a)
{
    push(&data->stacks->b, 9);
    insert_element(data->stacks, write_inst);
    ASSERT_TRUE(is_stack_sorted_descending(&data->stacks->b));
}

CTEST2(sort_ascending_stack_b_test, stack_b_size_one_element_smaller_than_top_a)
{
    push(&data->stacks->b, 7);
    insert_element(data->stacks, write_inst);
    ASSERT_TRUE(is_stack_sorted_descending(&data->stacks->b));
}

CTEST2(sort_ascending_stack_b_test, basic_no_rotation_needed)
{
    push(&data->stacks->b, 0);
    push(&data->stacks->b, 2);
    push(&data->stacks->b, 7);
    insert_element(data->stacks, write_inst);
    ASSERT_TRUE(is_stack_sorted_descending(&data->stacks->b));
}

CTEST2(sort_ascending_stack_b_test, insert_bottom)
{
    push(&data->stacks->b, 9);
    push(&data->stacks->b, 10);
    push(&data->stacks->b, 11);
    insert_element(data->stacks, write_inst);
    ASSERT_TRUE(is_stack_sorted_descending(&data->stacks->b));
}

////////////////////////////////////////////
//                merge_test              //
////////////////////////////////////////////

// void insert_instruction_basic(const char *instruction, int times)
// {
//     (void)instruction;
//     (void)times;
// }

// CTEST_SKIP(merge_sort_test, basic_test)
// {
// 	int elements[1] = {300};
//     ASSERT_EQUAL(0, merge_sort(1, elements, insert_instruction_basic));
//     ASSERT_TRUE(is_list_sorted(1, elements));
// }

// CTEST_SKIP(merge_sort_test, two_sorted_elements)
// {
// 	int elements[2] = {1, 300};
//     ASSERT_EQUAL(0, merge_sort(2, elements, insert_instruction_basic));
//     ASSERT_TRUE(is_list_sorted(2, elements));
// }

// CTEST_SKIP(merge_sort_test, two_unsorted_elements)
// {
// 	int elements[2] = {4, 3};
//     ASSERT_EQUAL(1, merge_sort(2, elements, insert_instruction_basic));
//     ASSERT_TRUE(is_list_sorted(2, elements));
// }

// CTEST_SKIP(merge_sort_test, three_unsorted_elements)
// {
// 	int elements[3] = {4, 10, 0};
//     ASSERT_EQUAL(13, merge_sort(3, elements, insert_instruction_basic));
//     ASSERT_TRUE(is_list_sorted(3, elements));
// }

// CTEST_SKIP(merge_sort_test, five_unsorted_elements)
// {
// 	int elements[5] = {5, 3, 4, 1, 2};
//     ASSERT_EQUAL(24, merge_sort(5, elements, insert_instruction_basic));
//     ASSERT_TRUE(is_list_sorted(5, elements));
// }

// CTEST_SKIP(merge_sort_test, seven_unsorted_elements)
// {
// 	int elements[7] = {5, 3, 4, 1, 2, 6, 7};
//     merge_sort(7, elements, insert_instruction_basic);
//     ASSERT_TRUE(is_list_sorted(7, elements));
// }

// CTEST_SKIP(merge_sort_test, seven_unsorted_elements_1)
// {
// 	int elements[7] = {5, 3, 4, 1, 2, 10, 9};
//     merge_sort(7, elements, insert_instruction_basic);
//     ASSERT_TRUE(is_list_sorted(7, elements));
// }
