#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = ft_strlen(s);
	c = (unsigned char)c;
	ptr = (char *)s;
	while (i >= 0)
	{
		if (ptr[i] == c)
			return (&ptr[i]);
		--i;
	}
	return (NULL);
}
