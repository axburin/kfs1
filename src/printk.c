#include "kernel.h"

int	ft_handle_format(va_list arg, const char str)
{
	int	count;

	count = 0;
	if (str == 'c')
		count = ft_putchar_m(va_arg(arg, int));
	else if (str == 's')
		count = ft_putstr_m(va_arg(arg, char *));
	else if (str == 'p')
		count = ft_putptr(va_arg(arg, void *));
	else if (str == 'd' || str == 'i')
		count = ft_putint(va_arg(arg, int));
	else if (str == 'u')
		count = ft_putint_unsigned(va_arg(arg, unsigned int));
	else if (str == 'x')
		count += ft_puthexa(va_arg(arg, unsigned int));
	else if (str == 'X')
		count += ft_puthexa_upper(va_arg(arg, unsigned int));
	else if (str == '%')
		count = ft_putchar_m('%');
	return (count);
}

int	printk(const char *str, ...)
{
	uint32_t	i;
	int			return_value;
	va_list		arg;

	i = 0;
	return_value = 0;
	va_start(arg, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			return_value += ft_handle_format(arg, str[i]);
		}
		else
			return_value += ft_putchar_m(str[i]);
		i++;
	}
	va_end(arg);
	return (return_value);
}
