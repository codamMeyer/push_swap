#include "ctest.h"
#include <push_swap/bubble_sort.h>
#include <push_swap/merge_sort.h>
#include <push_swap/special_cases_sort.h>
#include <parser/parse_instructions.h>
#include <push_swap/push_swap.h>
#include <utils/status.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

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
//                merge_test              //
////////////////////////////////////////////

// void	insert_instruction_basic(const char *instruction, int times)
// {
//     const t_instructions solution[15] = {PB, PB, SB, PB, SB, PA, PA, PA, PB, PB, SB, PB, PA, PA, PA};
//     static int instruction_index = 0;
// 	int i = 0;
// 	while (i < times)
// 	{
//         t_instructions cur = get_instruction(instruction);
//         ASSERT_EQUAL(solution[instruction_index++], cur);
//         ++i;
// 	}
// }

void insert_instruction_basic(const char *instruction, int times)
{
    (void)instruction;
    (void)times;
}

CTEST(merge_sort_test, basic_test)
{
	int elements[1] = {300};
    ASSERT_EQUAL(0, merge_sort(1, elements, insert_instruction_basic));
    ASSERT_TRUE(is_list_sorted(1, elements));
}

CTEST(merge_sort_test, two_sorted_elements)
{
	int elements[2] = {1, 300};
    ASSERT_EQUAL(0, merge_sort(2, elements, insert_instruction_basic));
    ASSERT_TRUE(is_list_sorted(2, elements));
}

CTEST(merge_sort_test, two_unsorted_elements)
{
	int elements[2] = {4, 3};
    ASSERT_EQUAL(1, merge_sort(2, elements, insert_instruction_basic));
    ASSERT_TRUE(is_list_sorted(2, elements));
}

CTEST(merge_sort_test, three_unsorted_elements)
{
	int elements[3] = {4, 10, 0};
    ASSERT_EQUAL(13, merge_sort(3, elements, insert_instruction_basic));
    ASSERT_TRUE(is_list_sorted(3, elements));
}

CTEST_SKIP(merge_sort_test, five_unsorted_elements)
{
	int elements[5] = {5, 3, 4, 1, 2};
    ASSERT_EQUAL(24, merge_sort(5, elements, insert_instruction_basic));
    ASSERT_TRUE(is_list_sorted(5, elements));
}

CTEST(merge_sort_test, seven_unsorted_elements)
{
	int elements[7] = {5, 3, 4, 1, 2, 6, 7};
    merge_sort(7, elements, insert_instruction_basic);
    ASSERT_TRUE(is_list_sorted(7, elements));
}

CTEST_SKIP(merge_sort_test, seven_unsorted_elements_1)
{
	int elements[7] = {5, 3, 4, 1, 2, 10, 9};
    merge_sort(7, elements, insert_instruction_basic);
    ASSERT_TRUE(is_list_sorted(7, elements));
}
