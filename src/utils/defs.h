#ifndef DEFS_H
# define DEFS_H
# define TRUE 1
# define FALSE 0

typedef int	t_bool;
typedef struct s_flags
{
	t_bool	verbose;
	t_bool	color;
	t_bool	file_output;
	t_bool	total;
	t_bool	is_valid;
}	t_flags;

typedef enum e_valid_flags
{
	VERBOSE = 'v',
	COLOR = 'c',
	FILE_OUTPUT = 'f',
	TOTAL = 't'
}	t_valid_flags;

#endif