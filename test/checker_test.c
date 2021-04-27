#include "ctest.h"
#include <parser/parse_numbers.h>
#include <parser/parse_instructions.h>
#include <checker/processor.h>
#include <checker/checker.h>

//////////////////////////////////////////////
//       	 is_stack_sorted_test           //
//////////////////////////////////////////////

CTEST(is_stack_sorted_test, one_element)
{
	int elements[1];
	t_stack stack = {.elements = (int *)elements, .top = -1};
	push(&stack, 1);
	ASSERT_EQUAL(OK, is_stack_sorted(&stack));
}

CTEST(is_stack_sorted_test, three_sorted_elements)
{
	int elements[3];
	t_stack stack = {.elements = (int *)elements, .top = -1};
	push(&stack, 1);
	push(&stack, 0);
	push(&stack, -1);
	ASSERT_EQUAL(OK, is_stack_sorted(&stack));
}

CTEST(is_stack_sorted_test, three_not_sorted_elements)
{
	int elements[3];
	t_stack stack = {.elements = (int *)elements, .top = -1};
	push(&stack, -1);
	push(&stack, 0);
	push(&stack, 2);
	ASSERT_EQUAL(KO, is_stack_sorted(&stack));
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

//////////////////////////////////////////////
//         				run_test            //
//////////////////////////////////////////////

t_instructions process_sorted_elements()
{
	static int i = 0;
	static const t_instructions inst[2] = {END_OF_INSTRUCTIONS, END_OF_INSTRUCTIONS};
	return (inst[i++]);
}

CTEST(run_test, sorted_elements)
{	
	const char *argv[] = {"1", "2", "3", "4"};
	ASSERT_EQUAL(OK, run_checker(4, argv, process_sorted_elements));
}

CTEST(run_test, invalid_number)
{	
	const char *argv[] = {"A1", "2", "3", "4"};
	ASSERT_EQUAL(ERROR, run_checker(4, argv, process_sorted_elements));
}

t_instructions process_invalid_instruction()
{
	static int i = 0;
	static const t_instructions inst[1] = {INVALID_INSTRUCTION};
	return (inst[i++]);
}

CTEST(run_test, invalid_instruction)
{	
	const char *argv[] = {"1", "2", "3", "4"};
	ASSERT_EQUAL(ERROR, run_checker(4, argv, process_invalid_instruction));
}

t_instructions process_unsorted_elements()
{
	static int i = 0;
	static const t_instructions inst[2] = {RA, END_OF_INSTRUCTIONS};
	return (inst[i++]);
}

CTEST(run_test, unsorted_elements)
{	
	const char *argv[] = {"5", "2", "3", "4"};
	ASSERT_EQUAL(OK, run_checker(4, argv, process_unsorted_elements));
}

t_instructions process_unsorted_elements_incorrect()
{
	static int i = 0;
	static const t_instructions inst[2] = {SA, END_OF_INSTRUCTIONS};
	return (inst[i++]);
}

CTEST(run_test, unsorted_elements_incorrect_solution)
{	
	const char *argv[] = {"5", "2", "3", "4"};
	ASSERT_EQUAL(KO, run_checker(4, argv, process_unsorted_elements_incorrect));
}

t_instructions process_solution_set()
{
	static int i = 0;
	static const t_instructions inst[28] = {PB,PB,SB,PB,SB,PB,SB,PB,SB,PA,PA,PA,PA,PA,PB,PB,SB,PB,SB,PB,SB,PB,PA,PA,PA,PA,PA,END_OF_INSTRUCTIONS};
	return (inst[i++]);
}

CTEST(run_test, solution_set_solution)
{	
	const char *argv[] = {"5", "4", "1", "2", "3"};
	ASSERT_EQUAL(OK, run_checker(5, argv, process_solution_set));
}