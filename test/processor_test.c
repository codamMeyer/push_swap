#include "ctest.h"
#include "../src_checker/stack.h"
#include "../src_checker/processor.h"

//////////////////////////////////////////////
//             sa_sb_ss_test                //
//////////////////////////////////////////////

CTEST_DATA(sa_sb_ss_test)
{
	t_stack_pair stacks_;
    t_stack_pair *stacks;
};

CTEST_SETUP(sa_sb_ss_test)
{
    data->stacks = &data->stacks_;
	data->stacks->a.top = -1;
	data->stacks->b.top = -1;
}

CTEST_TEARDOWN(sa_sb_ss_test)
{
	(void)data;
}

CTEST2(sa_sb_ss_test, sa_test)
{
	push(&(data->stacks->a), 1);
	push(&(data->stacks->a), 2);
	sa(data->stacks);
    ASSERT_EQUAL(2, data->stacks->a.elements[0]);
    ASSERT_EQUAL(1, data->stacks->a.elements[1]);
}

CTEST2(sa_sb_ss_test, sb_test)
{
	push(&(data->stacks->b), 1);
	push(&(data->stacks->b), 2);
	sb(data->stacks);
    ASSERT_EQUAL(2, data->stacks->b.elements[0]);
    ASSERT_EQUAL(1, data->stacks->b.elements[1]);
}

CTEST2(sa_sb_ss_test, ss_test)
{
	push(&(data->stacks->a), 3);
	push(&(data->stacks->a), 4);

	push(&(data->stacks->b), 5);
	push(&(data->stacks->b), 6);
	ss(data->stacks);
	ASSERT_EQUAL(4, data->stacks->a.elements[0]);
    ASSERT_EQUAL(3, data->stacks->a.elements[1]);
    ASSERT_EQUAL(6, data->stacks->b.elements[0]);
    ASSERT_EQUAL(5, data->stacks->b.elements[1]);
}

//////////////////////////////////////////////
//       	      pa_pb_test                //
//////////////////////////////////////////////

CTEST_DATA(pa_pb_test)
{
	t_stack_pair stacks_;
    t_stack_pair *stacks;
};

CTEST_SETUP(pa_pb_test)
{
    data->stacks = &data->stacks_;
	data->stacks->a.top = -1;
	data->stacks->b.top = -1;
}

CTEST_TEARDOWN(pa_pb_test)
{
	(void)data;
}

CTEST2(pa_pb_test, pa_empty_stack_b)
{
	pa(data->stacks);
    ASSERT_EQUAL(-1, data->stacks->a.top);
    ASSERT_EQUAL(0, size(&(data->stacks->a)));
    ASSERT_EQUAL(0, size(&(data->stacks->b)));
}

CTEST2(pa_pb_test, pa_one_element_stack_b)
{
	push(&(data->stacks->b), 5);
	pa(data->stacks);
    ASSERT_EQUAL(1, size(&(data->stacks->a)));
	ASSERT_EQUAL(0, size(&(data->stacks->b)));
}

CTEST2(pa_pb_test, pb_empty_stack_a)
{
	pb(data->stacks);
    ASSERT_EQUAL(-1, data->stacks->b.top);
    ASSERT_EQUAL(0, size(&(data->stacks->b)));
    ASSERT_EQUAL(0, size(&(data->stacks->a)));
}

CTEST2(pa_pb_test, pb_one_element_stack_a)
{
	push(&(data->stacks->a), 5);
	pb(data->stacks);
    ASSERT_EQUAL(1, size(&(data->stacks->b)));
	ASSERT_EQUAL(0, size(&(data->stacks->a)));
}

//////////////////////////////////////////////
//       	   ra_rb_rr_test                //
//////////////////////////////////////////////

CTEST_DATA(ra_rb_rr_test)
{
	t_stack_pair stacks_;
    t_stack_pair *stacks;
};

CTEST_SETUP(ra_rb_rr_test)
{
    data->stacks = &data->stacks_;
	data->stacks->a.top = -1;
	data->stacks->b.top = -1;
}

CTEST_TEARDOWN(ra_rb_rr_test)
{
	(void)data;
}

CTEST2_SKIP(ra_rb_rr_test, ra_empty_stack)
{
	(void)data;
    ASSERT_TRUE(1);
}

//////////////////////////////////////////////
//       		rra_rrb_rrr_test            //
//////////////////////////////////////////////

CTEST_DATA(rra_rrb_rrr_test)
{
	t_stack_pair stacks_;
    t_stack_pair *stacks;
};

CTEST_SETUP(rra_rrb_rrr_test)
{
    data->stacks = &data->stacks_;
	data->stacks->a.top = -1;
	data->stacks->b.top = -1;
}

CTEST_TEARDOWN(rra_rrb_rrr_test)
{
	(void)data;
}

CTEST2_SKIP(rra_rrb_rrr_test, empty_stack)
{
	(void)data;
    ASSERT_TRUE(1);
}