#include "kernel.h"

int	ft_putchar_m(int c) {
	char str[2] = {(char)c, '\0'};
    print(str);
	return (1);
}

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - ('a' - 'A'));
	else
		return (c);
}

int	ft_puthexa(unsigned long nb, int n)
{
	if (nb > 15)
		n = ft_puthexa(nb / 16, n);
	n += ft_putchar_m(HEX[nb % 16]);
	return (n);
}

int	ft_puthexa_upper(unsigned long nb, int n)
{
	if (nb > 15)
		n += ft_puthexa_upper(nb / 16, n);
	n += ft_putchar_m(ft_toupper(HEX[nb % 16]));
	return (n);
}

int	ft_putint_unsigned(int nbr)
{
	int				i;
	unsigned int	nb;

	i = 0;
	nb = (unsigned)nbr;
	if (nb > 9)
		i += ft_putint(nb / 10);
	i += ft_putchar_m((nb % 10) + '0');
	return (i);
}

int	ft_putstr_m(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putstr_m("(null)"));
	while (str[i] != '\0')
		i += ft_putchar_m(str[i]);
	return (i);
}

int	ft_putptr(void *ptr)
{
	int				count;
	unsigned long	nb;

	nb = (unsigned long)ptr;
	if (!ptr)
		return (ft_putstr_m("(nil)"));
	count = ft_putstr_m("0x");
	return (ft_puthexa(nb, count));
}

int	ft_putint(int nbr)
{
	int		i;
	long	nb;

	i = 0;
	nb = (long)nbr;
	if (nb < 0)
	{
		nb = -nb;
		i += ft_putchar_m('-');
	}
	if (nb > 9)
		i += ft_putint(nb / 10);
	i += ft_putchar_m((nb % 10) + '0');
	return (i);
}
