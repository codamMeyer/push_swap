#include "ctest.h"
#include <math.h>
#include <utils/math_utils.h>
#include <stdio.h>

CTEST(floor, test)
{
    double expected = floor(3.00);
    double actual = ft_floor(3.00);
    ASSERT_DBL_NEAR_TOL(expected, actual, 0);

    expected = floor(3.50);
    actual = ft_floor(3.50);
    ASSERT_DBL_NEAR_TOL(expected, actual, 0);

}

CTEST(ceil, test)
{
    double expected = ceil(3.00);
    double actual = ft_ceil(3.00);
    ASSERT_DBL_NEAR_TOL(expected, actual, 0);

    expected = ceil(3.50);
    actual = ft_ceil(3.50);
    ASSERT_DBL_NEAR_TOL(expected, actual, 0);

}