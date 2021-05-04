#include "libft.h"

void	ft_putnstr_fd(const char *s, int fd, int len)
{
	if (s == NULL || fd < 0)
		return ;
	write(fd, s, len);
}
