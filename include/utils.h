#ifndef UTILS_H
# define UTILS_H

#include "stdint.h"

void	*ft_memset(void *s, int c, uint32_t n);
void	hex_to_str(unsigned int addr, char *result, int size);
void	kdump(uint32_t addr, int limit);

#endif