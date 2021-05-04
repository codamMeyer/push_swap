#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*copy_s;
	int		i;

	i = 0;
	copy_s = (char *)s;
	while (copy_s[i] != '\0')
	{
		if (copy_s[i] == (char)c)
			return (&copy_s[i]);
		++i;
	}
	if ((char)c == '\0')
		return (&copy_s[i]);
	return (NULL);
}
