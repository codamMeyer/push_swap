#include "checker.h"
#include <utils/status.h>
#include <parser/parse_instructions.h>
#include <stdlib.h>

int	main(int argc, const char *argv[])
{
	t_status	ret;

	if (argc < 2)
		return (ERROR);
	ret = run_checker(argc - 1, &(argv[1]), get_next_instruction);
	print_message(ret);
	exit(ret);
}
