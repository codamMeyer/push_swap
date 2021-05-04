#include "libft.h"

static char	*ft_strcopy(char *dest, const char *src)
{
	int	i;

	if (src == 0 || dest == 0)
		return (dest);
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char		*cpy;
	const int	length = ft_strlen((char *)s);

	cpy = (char *)malloc(length + 1);
	if (cpy == NULL)
		return (NULL);
	ft_strcopy(cpy, s);
	return (cpy);
}
