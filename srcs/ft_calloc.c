#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;
	size_t	total;

	total = size * nmemb;
	if (size != 0 && nmemb != 0 && (total < nmemb || total < size))
		return (NULL);
	result = (void *)malloc(total);
	if (result == 0)
		return (0);
	ft_bzero(result, total);
	return (result);
}
