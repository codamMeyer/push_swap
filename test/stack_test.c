#include "ctest.h"
#include "../src_checker/stack.h"

//////////////////////////////////////////////
//                 size_test                //
//////////////////////////////////////////////

CTEST_DATA(size_test)
{
	t_stack stack_;
    t_stack *stack;
};

CTEST_SETUP(size_test)
{
    data->stack = &data->stack_;
	data->stack->top = -1;
}

CTEST_TEARDOWN(size_test)
{
	(void)data;
}

CTEST2(size_test, empty_stack)
{
    ASSERT_EQUAL(0, size(data->stack));
}

CTEST2(size_test, non_empty_stack)
{
    data->stack->top = 5;
    ASSERT_EQUAL(6, size(data->stack));
}

//////////////////////////////////////////////
//                 push_test                //
//////////////////////////////////////////////

CTEST_DATA(push_test)
{
	t_stack stack_;
    t_stack *stack;
};

CTEST_SETUP(push_test)
{
    data->stack = &data->stack_;
	data->stack->top = -1;
}

CTEST_TEARDOWN(push_test)
{
	(void)data;
}

CTEST2(push_test, to_empty_stack)
{
	push(data->stack, 6);
    ASSERT_EQUAL(0, data->stack->top);
    ASSERT_EQUAL(6, data->stack->elements[data->stack->top]);
    ASSERT_EQUAL(1, size(data->stack));
}

CTEST2(push_test, to_non_empty_stack)
{
    data->stack->top = 0;
    data->stack->elements[data->stack->top] = 5;
	push(data->stack, 8);
    ASSERT_EQUAL(1, data->stack->top);
    ASSERT_EQUAL(8, data->stack->elements[data->stack->top]);
    ASSERT_EQUAL(2, size(data->stack));
}


//////////////////////////////////////////////
//               rotate_test                //
//////////////////////////////////////////////

// CTEST_DATA(rotate_test)
// {
// 	t_stack stack_;
//     t_stack *stack;
// };

// CTEST_SETUP(rotate_test)
// {
//     data->stack = &data->stack_;
// 	data->stack->top = -1;
// }

// CTEST_TEARDOWN(rotate_test)
// {
// 	(void)data;
// }

// CTEST2(rotate_test, empty_stack)
// {
//     ASSERT_EQUAL(0, data->stack->top);
//     ASSERT_EQUAL(6, data->stack->elements[data->stack->top]);
//     ASSERT_EQUAL(1, size(data->stack));
// }

// CTEST2(rotate_test, two_elements_stack)
// {
//     data->stack->top = 0;
//     data->stack->elements[data->stack->top] = 5;
// 	push(data->stack, 8);
//     ASSERT_EQUAL(1, data->stack->top);
//     ASSERT_EQUAL(8, data->stack->elements[data->stack->top]);
//     ASSERT_EQUAL(2, size(data->stack));
// }