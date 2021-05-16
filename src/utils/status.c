#include "status.h"
#include <libft.h>
#include <unistd.h>

void	print_message(t_status status)
{
	const char	*status_message[4] = {
		"OK\n",
		"KO\n",
		"Error\n",
		"",
	};
	const int	len = ft_strlen(status_message[(int)status]);

	write(STDERR_FILENO, status_message[(int)status], len);
}
