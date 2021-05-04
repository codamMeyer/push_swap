#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	number;

	if (fd < 0)
		return ;
	if (n == INT_MIN)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n / 10 > 0)
		ft_putnbr_fd(n / 10, fd);
	number = n % 10 + '0';
	write(fd, &number, 1);
}
