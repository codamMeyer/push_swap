#include "ctest.h"
#include <push_swap/bubble_sort.h>
#include <parser/parse_instructions.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

//////////////////////////////////////////////
//       	     bubble_sort_test            //
//////////////////////////////////////////////

void	blah(const char *instruction, int times)
{
    (void)instruction;
    (void)times;
    ASSERT_TRUE(0);
}

CTEST(bubble_sort_test, one_element)
{
	int elements[1] = {1};
    ASSERT_EQUAL(0, bubble_sort(1, elements, blah));
}

CTEST(bubble_sort_test, two_sorted_elements)
{
	int elements[2] = {1, 2};
    ASSERT_EQUAL(0, bubble_sort(2, elements, blah));
}

CTEST(bubble_sort_test,five_sorted_elements)
{
	int elements[5] = {1, 2, 6, 9, 300};
    ASSERT_EQUAL(0, bubble_sort(5, elements, blah));
}

void	insert_instruction_3_unsorted_elements(const char *instruction, int times)
{
    t_instructions sort_three_elements[15] = {PB, PB, SB, PB, SB, PA, PA, PA, PB, PB, SB, PB, PA, PA, PA};
	int	i;
    static int instruction_index = 0;
	i = 0;
	while (i < times)
	{
        t_instructions cur = get_instruction(instruction);
        ASSERT_EQUAL(sort_three_elements[instruction_index++], cur);
        ++i;
	}
}

CTEST(bubble_sort_test, three_unsorted_elements_47_total)
{
	int elements[3] = {300, 6, 2};
    ASSERT_EQUAL(15, bubble_sort(3, elements, insert_instruction_3_unsorted_elements));
}

// CTEST(bubble_sort_test,five_unsorted_elements_47_total)
// {
// 	int elements[5] = {300, 6, 2, 1, 30};
//     ASSERT_EQUAL(37, bubble_sort(5, elements, insert_instruction));
// }

// CTEST(bubble_sort_test, five_unsorted_elements_37_total)
// {
// 	int elements[5] = {5, 4, 1, 2, 3};
//     ASSERT_EQUAL(27, bubble_sort(5, elements, insert_instruction));
// }
