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

void	hex_to_str(unsigned int addr, char *result, int size)
{
	int	len;
	char	base_str[16] = "0123456789abcdef";

	len = size - 1;
	ft_memset(result, '0', size);
	result[size - 1] = 0;
	while (addr != 0)
	{
		result[--len] = base_str[addr % 16];
		addr = addr / 16;
	}
}

void kdump(uint32_t addr, int limit)
{
    char *c = (char *)addr;
    char str_addr[9];
    int i;
    uint32_t previous;

    if (limit <= 0)
        return;

    for (i = 0; i < limit; i++) {
        if ((i % 16) == 0) {
            if (i != 0) {
                previous = addr - 16;
                while (previous < addr) {
                    if (*(char *)previous <= 32)
                        printk("%c", '.');
                    else
                        printk("%c", *(char *)previous);
                    previous++;
                }
                printk("\n");
            }
            printk("%p: ", addr);
        }
        hex_to_str((uint32_t)c[i], str_addr, 3);
        printk("%s ", str_addr);
        addr++;
    }
    for (i = 0; i < ((limit % 16) * 3); i++) {
        printk(" ");
    }
    if ((limit % 16) == 0) {
        previous = addr - 16;
    } else {
        previous = addr - (limit % 16);
    }
    while (previous < addr) {
        if (*(char *)previous <= 32)
            printk("%c", '.');
        else
            printk("%c", *(char *)previous);
        previous++;
    }
    printk("\n==========END============\n");
    printk("\n");
}