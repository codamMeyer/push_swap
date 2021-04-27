#include "ctest.h"
#include "../src/checker/stack.h"

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

////////////////////////////////////////////
//             rotate_test                //
////////////////////////////////////////////

CTEST_DATA(rotate_test)
{
	t_stack stack_;
    t_stack *stack;
};

CTEST_SETUP(rotate_test)
{
    data->stack = &data->stack_;
	data->stack->top = -1;
}

CTEST_TEARDOWN(rotate_test)
{
	(void)data;
}

CTEST2(rotate_test, empty_stack)
{
    rotate(data->stack);
    ASSERT_EQUAL(0, size(data->stack));
}

CTEST2(rotate_test, one_element_stack)
{
	push(data->stack, 8);
    rotate(data->stack);
    ASSERT_EQUAL(1, size(data->stack));
    ASSERT_EQUAL(8, data->stack->elements[data->stack->top]);
}

CTEST2(rotate_test, two_elements_stack)
{
	push(data->stack, 1);
    push(data->stack, 2); 
    rotate(data->stack);
    ASSERT_EQUAL(2, size(data->stack));
    ASSERT_EQUAL(1, data->stack->elements[data->stack->top]);
    ASSERT_EQUAL(2, data->stack->elements[0]);
}


CTEST2(rotate_test, four_elements_stack)
{
	push(data->stack, 3);
    push(data->stack, 2);
    push(data->stack, 1);
    push(data->stack, 4);
      
    rotate(data->stack);
    ASSERT_EQUAL(4, size(data->stack));
    ASSERT_EQUAL(3, data->stack->top);

    ASSERT_EQUAL(4, data->stack->elements[0]);
    ASSERT_EQUAL(3, data->stack->elements[1]);
    ASSERT_EQUAL(2, data->stack->elements[2]);
    ASSERT_EQUAL(1, data->stack->elements[3]);
}

////////////////////////////////////////////
//           reverse_rotate_test          //
////////////////////////////////////////////

CTEST_DATA(reverse_rotate_test)
{
	t_stack stack_;
    t_stack *stack;
};

CTEST_SETUP(reverse_rotate_test)
{
    data->stack = &data->stack_;
	data->stack->top = -1;
}

CTEST_TEARDOWN(reverse_rotate_test)
{
	(void)data;
}

CTEST2(reverse_rotate_test, empty_stack)
{
    reverse_rotate(data->stack);
    ASSERT_EQUAL(0, size(data->stack));
}

CTEST2(reverse_rotate_test, one_element_stack)
{
	push(data->stack, 8);
    reverse_rotate(data->stack);
    ASSERT_EQUAL(1, size(data->stack));
    ASSERT_EQUAL(8, data->stack->elements[data->stack->top]);
}

CTEST2(reverse_rotate_test, two_elements_stack)
{
	push(data->stack, 1);
    push(data->stack, 2);

    reverse_rotate(data->stack);
    ASSERT_EQUAL(2, size(data->stack));
    ASSERT_EQUAL(1, data->stack->elements[data->stack->top]);
    ASSERT_EQUAL(2, data->stack->elements[0]);

}

CTEST2(reverse_rotate_test, four_elements_stack)
{
	push(data->stack, 1);
    push(data->stack, 4);
    push(data->stack, 3);
    push(data->stack, 2);

    reverse_rotate(data->stack);
    ASSERT_EQUAL(4, size(data->stack));
    ASSERT_EQUAL(3, data->stack->top);

    ASSERT_EQUAL(4, data->stack->elements[0]);
    ASSERT_EQUAL(3, data->stack->elements[1]);
    ASSERT_EQUAL(2, data->stack->elements[2]);
    ASSERT_EQUAL(1, data->stack->elements[3]);
}

////////////////////////////////////////////
//               pop_test                 //
////////////////////////////////////////////

CTEST_DATA(pop_test)
{
	t_stack stack_;
    t_stack *stack;
};

CTEST_SETUP(pop_test)
{
    data->stack = &data->stack_;
	data->stack->top = -1;
}

CTEST_TEARDOWN(pop_test)
{
	(void)data;
}

CTEST2(pop_test, empty_stack)
{
    t_optional_int element = pop(data->stack);
    ASSERT_FALSE(element.initialized);
}

CTEST2(pop_test, two_elements_stack)
{
    push(data->stack, 1);
    push(data->stack, 2);
    t_optional_int element = pop(data->stack);
    ASSERT_EQUAL(2, element.element);
    ASSERT_TRUE(element.initialized);
    ASSERT_EQUAL(1, size(data->stack));
}

////////////////////////////////////////////
//              swap_test                 //
////////////////////////////////////////////

CTEST_DATA(swap_test)
{
	t_stack stack_;
    t_stack *stack;
};

CTEST_SETUP(swap_test)
{
    data->stack = &data->stack_;
	data->stack->top = -1;
}

CTEST_TEARDOWN(swap_test)
{
	(void)data;
}

CTEST2(swap_test, empty_stack)
{
    swap_top_elements(data->stack);
    ASSERT_EQUAL(0, size(data->stack));
}

CTEST2(swap_test, one_element_stack)
{
    push(data->stack, 1);
    swap_top_elements(data->stack);

    ASSERT_EQUAL(1, size(data->stack));
    ASSERT_EQUAL(1, data->stack->elements[data->stack->top]);
}

CTEST2(swap_test, five_elements_stack)
{
    push(data->stack, 1);
    push(data->stack, 2);
    push(data->stack, 3);
    push(data->stack, 4);
    push(data->stack, 5);
    swap_top_elements(data->stack);
    ASSERT_EQUAL(5, size(data->stack));
    ASSERT_EQUAL(1, data->stack->elements[0]);
    ASSERT_EQUAL(2, data->stack->elements[1]);
    ASSERT_EQUAL(3, data->stack->elements[2]);
    ASSERT_EQUAL(5, data->stack->elements[3]);
    ASSERT_EQUAL(4, data->stack->elements[4]);
}

