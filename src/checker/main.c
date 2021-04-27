#include "checker.h"
#include <parser/parse_instructions.h>
#include <unistd.h>
#include <stdlib.h>

int	main(int argc, const char *argv[])
{
	t_status	ret;

	if (argc < 2)
		ret = ERROR;
	else
		ret = run_checker(argc - 1, &(argv[1]), get_next_instruction);
	if (ret == ERROR)
		write(STDOUT_FILENO, "Error\n", 6);
	else if (ret == OK)
		write(STDOUT_FILENO, "OK\n", 3);
	else
		write(STDOUT_FILENO, "KO\n", 3);
	exit(ret);
}
