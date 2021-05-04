#include <stddef.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*csrc;
	unsigned char		*cdest;
	const unsigned char	to_find = (unsigned char)c;
	size_t				i;

	i = 0;
	csrc = (unsigned char *)src;
	cdest = (unsigned char *)dest;
	while (i < n)
	{
		cdest[i] = csrc[i];
		if (csrc[i] == to_find)
			return (dest + i + 1);
		++i;
	}
	return (NULL);
}
