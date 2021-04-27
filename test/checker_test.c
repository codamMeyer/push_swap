#include "ctest.h"
#include "../src/parser/parse_numbers.h"
#include "../src/parser/parse_instructions.h"
#include "../src/checker/processor.h"
#include "../src/checker/checker.h"

//////////////////////////////////////////////
//       	 is_stack_sorted_test           //
//////////////////////////////////////////////

CTEST(is_stack_sorted_test, one_element)
{
	int elements[1] = {1};
	t_stack stack = {.elements = (int *)elements};

	ASSERT_TRUE(is_stack_sorted(stack, 1));
}

CTEST(is_stack_sorted_test, three_sorted_elements)
{
	int elements[3] = {-1, 0, 1};
	t_stack stack = {.elements = (int *)elements};
	ASSERT_TRUE(is_stack_sorted(stack, 3));
}

CTEST(is_stack_sorted_test, three_not_sorted_elements)
{
	int elements[3] = {2, -1, 0};
	t_stack stack = {.elements = (int *)elements};
	ASSERT_FALSE(is_stack_sorted(stack, 3));
}

//////////////////////////////////////////////
//       	 populate_stack_a_test          //
//////////////////////////////////////////////

CTEST(populate_stack_a_test, one_element)
{
	int new_elements[] = {1};
	int elements[1];
	t_stack_pair stacks ={
							.a.elements = (int *)elements,
							.a.top = -1,
						};

	populate_stack_a(new_elements, 1, &stacks);
	ASSERT_EQUAL(0, stacks.a.top);
	ASSERT_EQUAL(1, stacks.a.elements[0]);
}

CTEST(populate_stack_a_test, five_element)
{
	int new_elements[] = {1, 2, 3, 4, 5};
	int elements[5];
	t_stack_pair stacks ={
							.a.elements = (int *)elements,
							.a.top = -1,
						};
	populate_stack_a(new_elements, 5, &stacks);
	ASSERT_EQUAL(4, stacks.a.top);
	ASSERT_EQUAL(5, stacks.a.elements[0]);
	ASSERT_EQUAL(1, stacks.a.elements[stacks.a.top]);
}

//////////////////////////////////////////////
//         create_and_destroy_test          //
//////////////////////////////////////////////

CTEST(create_and_destroy_test, one_element)
{
	t_stack_pair stacks = create_stack_pair(5);
	ASSERT_TRUE(stacks.initialized);
	destroy_stack_pair(&stacks);
	ASSERT_FALSE(stacks.initialized);
}