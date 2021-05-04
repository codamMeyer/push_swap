#include "ctest.h"
#include <parser/parse_numbers.h>
#include <parser/parse_instructions.h>
#include <parser/parse_flags.h>
#include <checker/processor.h>
#include <checker/checker.h>
#include <utils/defs.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

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
	const char *argv[] = {""};
	data->elements = parse_numbers(1, argv);
    ASSERT_NULL(data->elements);
}

CTEST2(parse_numbers_test, one_invalid_element_test)
{
	const char *argv[] = {"A1"};
	data->elements = parse_numbers(1, argv);
    ASSERT_NULL(data->elements);
}

CTEST2(parse_numbers_test, one_valid_element_test)
{
	const char *argv[] = {"1"};
	data->elements = parse_numbers(1, argv);
	ASSERT_EQUAL(1, data->elements[0]);
}

CTEST2(parse_numbers_test, five_valid_elements_test)
{
	const char *argv[] = {"1", "2", "3", "-4", "5"};
	data->elements = parse_numbers(5, argv);
	ASSERT_EQUAL(1, data->elements[0]);
	ASSERT_EQUAL(2, data->elements[1]);
	ASSERT_EQUAL(3, data->elements[2]);
	ASSERT_EQUAL(-4, data->elements[3]);
	ASSERT_EQUAL(5, data->elements[4]);
}

CTEST2(parse_numbers_test, five_elements_one_invalid_test)
{
	const char *argv[] = {"1", "2", "3", "4A", "5"};
	data->elements = parse_numbers(5, argv);
	ASSERT_NULL(data->elements);
}

CTEST2(parse_numbers_test, int_min)
{
	const char *argv[] = {"-2147483648"};
	data->elements = parse_numbers(1, argv);
	ASSERT_EQUAL(INT_MIN, data->elements[0]);
}

CTEST2(parse_numbers_test, int_max)
{
	const char *argv[] = {"2147483647"};
	data->elements = parse_numbers(1, argv);
	ASSERT_EQUAL(INT_MAX, data->elements[0]);
}

CTEST2(parse_numbers_test, duplicate_test)
{
	const char *argv[] = {"1", "2", "3", "1", "5"};
	data->elements = parse_numbers(5, argv);
	ASSERT_NULL(data->elements);
}

CTEST2(parse_numbers_test, bigger_than_int_max_test)
{
	const char *argv[] = {"21474836499"};
	data->elements = parse_numbers(1, argv);
	ASSERT_NULL(data->elements);
}

CTEST2(parse_numbers_test, one_bigger_than_int_max_test)
{
	const char *argv[] = {"2147483649"};
	data->elements = parse_numbers(1, argv);
	ASSERT_NULL(data->elements);
}

CTEST2(parse_numbers_test, one_smaller_than_int_min_test)
{
	const char *argv[] = {"-2147483649"};
	data->elements = parse_numbers(1, argv);
	ASSERT_NULL(data->elements);
}

CTEST2(parse_numbers_test, smaller_than_int_min_test)
{
	const char *argv[] = {"-21474836488"};
	data->elements = parse_numbers(1, argv);
	ASSERT_NULL(data->elements);
}

//////////////////////////////////////////////
//        parse_instructions_test           //
//////////////////////////////////////////////

CTEST(parse_instructions_test, many_instructions_test)
{
	ASSERT_EQUAL(RRA, get_instruction("rra"));
	ASSERT_EQUAL(RRB, get_instruction("rrb"));
	ASSERT_EQUAL(RRR, get_instruction("rrr"));
	ASSERT_EQUAL(SA, get_instruction("sa"));
	ASSERT_EQUAL(SB, get_instruction("sb"));
	ASSERT_EQUAL(SS, get_instruction("ss"));
	ASSERT_EQUAL(PA, get_instruction("pa"));
	ASSERT_EQUAL(PB, get_instruction("pb"));
	ASSERT_EQUAL(RA, get_instruction("ra"));
	ASSERT_EQUAL(RB, get_instruction("rb"));
	ASSERT_EQUAL(RR, get_instruction("rr"));
	ASSERT_EQUAL(END_OF_INSTRUCTIONS, get_instruction("\0"));
	ASSERT_EQUAL(INVALID_INSTRUCTION, get_instruction("aa"));
	ASSERT_EQUAL(INVALID_INSTRUCTION, get_instruction(" ra"));
	ASSERT_EQUAL(INVALID_INSTRUCTION, get_instruction("ra "));
	ASSERT_EQUAL(INVALID_INSTRUCTION, get_instruction("rra "));
}


//////////////////////////////////////////////
//        	    parse_flags_test            //
//////////////////////////////////////////////

CTEST(parse_flags_test, argv_less_than_two_elements)
{
	const char *argv[] = {"-f"};
	int argc = 1;
	t_flags flags = parse_flags(&argc, argv);
	ASSERT_FALSE(flags.color);
	ASSERT_FALSE(flags.verbose);
	ASSERT_FALSE(flags.file_output);
}

CTEST(parse_flags_test, no_flag)
{
	const char *argv[] = {"3", "5"};
	int argc = 2;
	t_flags flags = parse_flags(&argc, argv);
	ASSERT_FALSE(flags.color);
	ASSERT_FALSE(flags.verbose);
	ASSERT_FALSE(flags.file_output);
}

CTEST(parse_flags_test, incomplet_flag_missing_letter)
{
	const char *argv[] = {"-", "5"};
	int argc = 2;
	t_flags flags = parse_flags(&argc, argv);
	ASSERT_FALSE(flags.color);
	ASSERT_FALSE(flags.verbose);
	ASSERT_FALSE(flags.file_output);
}

CTEST(parse_flags_test, incomplet_flag_missing_minus)
{
	const char *argv[] = {"fu", "5"};
	int argc = 2;
	t_flags flags = parse_flags(&argc, argv);
	ASSERT_FALSE(flags.color);
	ASSERT_FALSE(flags.verbose);
	ASSERT_FALSE(flags.file_output);
}

CTEST(parse_flags_test, invalid_flag)
{
	const char *argv[] = {"-u", "5"};
	int argc = 2;
	t_flags flags = parse_flags(&argc, argv);
	ASSERT_FALSE(flags.color);
	ASSERT_FALSE(flags.verbose);
	ASSERT_FALSE(flags.file_output);
}

CTEST(parse_flags_test, v_flag)
{
	const char *argv[] = {"-v", "5"};
	int argc = 2;
	t_flags flags = parse_flags(&argc, argv);
	ASSERT_FALSE(flags.color);
	ASSERT_TRUE(flags.verbose);
	ASSERT_FALSE(flags.file_output);
}

CTEST(parse_flags_test, vb_flag)
{
	const char *argv[] = {"-vb", "5"};
	int argc = 2;
	t_flags flags = parse_flags(&argc, argv);
	ASSERT_FALSE(flags.color);
	ASSERT_FALSE(flags.verbose);
	ASSERT_FALSE(flags.file_output);
}

CTEST(parse_flags_test, vcf_flag)
{
	const char *argv[] = {"-vcf", "5"};
	int argc = 2;
	t_flags flags = parse_flags(&argc, argv);
	ASSERT_TRUE(flags.color);
	ASSERT_TRUE(flags.verbose);
	ASSERT_TRUE(flags.file_output);
	
}