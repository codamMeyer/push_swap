#include "ctest.h"

CTEST_DATA(swap)
{	
};

CTEST_SETUP(swap)
{
	(void)data;
}

CTEST_TEARDOWN(swap)
{
	(void)data;
}

CTEST2(swap, sorted)
{
	(void)data;
	ASSERT_TRUE(1);
}


CTEST2(swap, sorted2)
{
	(void)data;
	ASSERT_TRUE(1);
}