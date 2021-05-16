#ifndef STATUS_H
# define STATUS_H

typedef enum e_status
{
	OK = 0,
	KO = 1,
	ERROR = 2,
	NO_PARAMETERS = 3,
}	t_status;

void	print_message(t_status status);

#endif