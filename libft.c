#include "philo.h"

short	my_putstr(char *str, int fd)
{
	while (str && *str)
	{
		write(fd, str, 1);
		str++;
	}
	return (1);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n > 9)
		ft_putnbr_fd(n / 10, 1);
	n %= 10;
	n += 48;
	write(1, &n, 1);
}

int	my_atoi(char *str)
{
	unsigned long long	n;

	n = 0;
	if (*str == '-')
		exit (my_putstr("server id should be a potisive number\n", 2));
	if (*str == '+' && *(str + 1))
		str++;
	while (*str > 47 && *str < 58)
	{
		n = n * 10 + *str - 48;
		str++;
	}
	if (*str)
		exit (my_putstr("server id should be a number\n", 2));
	return (n);
}