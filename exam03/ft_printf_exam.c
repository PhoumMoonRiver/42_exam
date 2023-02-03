#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_print_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str[i])
		i++;
	return (write(1, str, i));
}

void	ft_print_num(long long int num, int *len, int base)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (num < 0)
	{
		num *= -1;
		*len += write(1, "-", 1);
	}
	if (num >= base)
		ft_print_num(num / base, len,base);
	*len += write(1, &hex[num % base], 1);
}

int	ft_printf(const char *arg, ...)
{
	int	i;
	int	len;
	va_list	ptrarg;

	i = 0;
	len = 0;
	va_start(ptrarg, arg);
	while (arg[i])
	{
		if (arg[i] == '%' && (arg[i + 1] == 's' || arg[i + 1] == 'd' || arg[i + 1] == 'x'))
		{
			i++;
			if (arg[i] == 's')
				len += ft_print_str((char *)va_arg(ptrarg, char *));
			else if (arg[i] == 'd')
				ft_print_num((long long int)va_arg(ptrarg, int), &len, 10);
			else if (arg[i] == 'x')
				ft_print_num((long long int)va_arg(ptrarg, unsigned int), &len, 16);
		}
		else
			len += ft_putchar(arg[i]);
		i++;
	}
	va_end(ptrarg);
	return (len);
}

int	main(void)
{
	printf("len >>> |%d|\n", ft_printf("hi hello % ==> test my str|%s|\n ==> test my deci|%d|\n ==> test my hex|%x|\n", "Hello_World", -1234, -1234 ));
	printf("\n=====================================\n\n");
	printf("len >>> |%d|\n", printf("hi hello % ==> test my str|%s|\n ==> test my deci|%d|\n ==> test my hex|%x|\n", "Hello_World", -1234, -1234 ));
}
