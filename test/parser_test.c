#include "ctest.h"
#include "../src/parser/parse_numbers.h"
#include <stdlib.h>
#include <limits.h>

//////////////////////////////////////////////
//             parse_numbers_test           //
//////////////////////////////////////////////

CTEST_DATA(parse_numbers_test)
{
	int *elements;
};

CTEST_SETUP(parse_numbers_test)
{
	data->elements = NULL;
}

CTEST_TEARDOWN(parse_numbers_test)
{
	free(data->elements);
}

CTEST2(parse_numbers_test, empty_list_test)
{
	const char *list[] = {""};
	data->elements = parse_numbers(1, list);
    ASSERT_NULL(data->elements);
}

CTEST2(parse_numbers_test, one_invalid_element_test)
{
	const char *list[] = {"A1"};
	data->elements = parse_numbers(1, list);
    ASSERT_NULL(data->elements);
}

CTEST2(parse_numbers_test, one_valid_element_test)
{
	const char *list[] = {"1"};
	data->elements = parse_numbers(1, list);
	ASSERT_EQUAL(1, data->elements[0]);
}

CTEST2(parse_numbers_test, five_valid_elements_test)
{
	const char *list[] = {"1", "2", "3", "-4", "5"};
	data->elements = parse_numbers(5, list);
	ASSERT_EQUAL(1, data->elements[0]);
	ASSERT_EQUAL(2, data->elements[1]);
	ASSERT_EQUAL(3, data->elements[2]);
	ASSERT_EQUAL(-4, data->elements[3]);
	ASSERT_EQUAL(5, data->elements[4]);
}

CTEST2(parse_numbers_test, five_elements_one_invalid_test)
{
	const char *list[] = {"1", "2", "3", "4A", "5"};
	data->elements = parse_numbers(5, list);
	ASSERT_NULL(data->elements);
}

CTEST2(parse_numbers_test, int_min)
{
	const char *list[] = {"-2147483648"};
	data->elements = parse_numbers(1, list);
	ASSERT_EQUAL(INT_MIN, data->elements[0]);
}

CTEST2(parse_numbers_test, int_max)
{
	const char *list[] = {"2147483647"};
	data->elements = parse_numbers(1, list);
	ASSERT_EQUAL(INT_MAX, data->elements[0]);
}

CTEST2(parse_numbers_test, duplicate_test)
{
	const char *list[] = {"1", "2", "3", "1", "5"};
	data->elements = parse_numbers(5, list);
	ASSERT_NULL(data->elements);
}