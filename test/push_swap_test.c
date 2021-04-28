#include "ctest.h"
#include <push_swap/bubble_sort.h>

//////////////////////////////////////////////
//       	     bubble_sort_test            //
//////////////////////////////////////////////

CTEST(bubble_sort_test, one_element)
{
	int elements[1] = {1};
    ASSERT_EQUAL(0, bubble_sort(1, elements));
}

CTEST(bubble_sort_test, two_sorted_elements)
{
	int elements[2] = {1, 2};
    ASSERT_EQUAL(0, bubble_sort(2, elements));
}

CTEST(bubble_sort_test,five_sorted_elements)
{
	int elements[5] = {1, 2, 6, 9, 300};
    ASSERT_EQUAL(0, bubble_sort(5, elements));
}

CTEST(bubble_sort_test,five_unsorted_elements_47_total)
{
	int elements[5] = {300, 6, 2, 1, 30};
    ASSERT_EQUAL(37, bubble_sort(5, elements));
}

CTEST(bubble_sort_test, five_unsorted_elements_37_total)
{
	int elements[5] = {5, 4, 1, 2, 3};
    ASSERT_EQUAL(27, bubble_sort(5, elements));
}
