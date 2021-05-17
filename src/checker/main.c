#include "checker.h"
#include <parser/parse_instructions.h>
#include <stdlib.h>
#include <utils/status.h>

int	main(int argc, const char *argv[])
{
	t_status	ret;
	int			num_elements;

	num_elements = argc - 1;
	if (argc < 2)
		return (ERROR);
	ret = run_checker(&num_elements, &(argv[1]), get_next_instruction);
	if (num_elements > 0)
		print_message(ret);
	exit(ret);
}
