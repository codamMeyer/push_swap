#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len_src;

	if (src == NULL)
		return (0);
	len_src = ft_strlen((char *)src);
	if (dest == NULL || size == 0)
		return (len_src);
	i = 0;
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return (len_src);
}
