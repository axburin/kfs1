#ifndef PRINTK_H
# define PRINTK_H

# ifndef HEX
#  define HEX "0123456789abcdef"
# endif

int	printk(const char *str, ...);
int	ft_putchar_m(int c);
int	ft_putstr_m(char *str);
int	ft_putptr(void *ptr);
int	ft_putint(int nbr);
int	ft_putint_unsigned(int nbr);
int	ft_puthexa_upper(unsigned long nb, int n);
int	ft_puthexa(unsigned long nb, int n);

#endif