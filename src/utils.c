#include "kernel.h"

void	*ft_memset(void *s, int c, uint32_t n)
{
	uint32_t		i = 0;
	unsigned char	*d;

	d = (unsigned char *)s;
	while (i < n) {
		d[i] = (unsigned char)c;
		i++;
	}
	return (s);
}