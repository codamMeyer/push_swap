#include "math_utils.h"

double ft_floor(double n) 
{
    const int number = (int)n;

    return ((double)number);
}

double ft_ceil(double n) 
{
    const int number = (int)n;

    if (n > (double)number)
        return ((double)number + 1);
    return ((double)number);
}
