#include "ctest.h"
#include <push_swap/bubble_sort.h>
#include <parser/parse_instructions.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

//////////////////////////////////////////////
//       	     bubble_sort_test            //
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

