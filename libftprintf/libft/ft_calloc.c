#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	const size_t	num_bites = nmemb * size;

	ptr = malloc(num_bites);
	if (ptr == 0)
		return (ptr);
	ft_bzero(ptr, num_bites);
	return (ptr);
}
