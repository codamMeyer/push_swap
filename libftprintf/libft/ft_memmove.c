#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int					i;
	const unsigned char	*csrc = (unsigned char *)src;
	unsigned char		*cdest;

	cdest = (unsigned char *)dest;
	if (dest == src || n == 0)
		return (dest);
	if (dest > src && dest - src < (int)n)
	{
		i = n - 1;
		while (i >= 0)
		{
			cdest[i] = csrc[i];
			i--;
		}
		return (dest);
	}
	ft_memcpy(dest, src, n);
	return (dest);
}
