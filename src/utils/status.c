#include "status.h"
#include <libft.h>
#include <stdio.h>
#include <unistd.h>

void	print_message(t_status status)
{
	const char	*red = "\033[01;31m";
	const char	*green = "\033[01;32m";
	const char	*status_message[14] = {
		"[OK]\n",
		"[KO]\n",
		"Error\n",
	};
	const int	len = ft_strlen(status_message[(int)status]);

	if (status == OK)
		write(STDOUT_FILENO, green, ft_strlen(green));
	else
		write(STDOUT_FILENO, red, ft_strlen(red));
	write(STDERR_FILENO, status_message[(int)status], len);
}
