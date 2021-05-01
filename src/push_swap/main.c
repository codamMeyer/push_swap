#include "push_swap.h"
#include <utils/status.h>
#include <parser/parse_numbers.h>
#include <stdlib.h>

int	main(int argc, const char *argv[])
{
	t_status	ret;

	if (argc < 2)
		exit(1);
	ret = run_push_swap(argc - 1, &(argv[1]));
	exit(ret);
}
