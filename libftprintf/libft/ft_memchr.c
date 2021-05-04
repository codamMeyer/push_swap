#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*copy_s;
	size_t			i;

	i = 0;
	copy_s = (unsigned char *)s;
	c = (unsigned char)c;
	while (i < n)
	{
		if (copy_s[i] == c)
			return (&copy_s[i]);
		++i;
	}
	return (NULL);
}
