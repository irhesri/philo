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

short	error(char *str, short n)
{
	if (n == 0)
		my_putstr(str, 2);
	else if (n == 1)
		my_putstr("pthread_mutex_lock() failed\n", 2);
	else if (n == 2)
		my_putstr("pthread_mutex_unlock() failed\n", 2);
	else if (n == 3)
		my_putstr("gettimeofday() failed\n", 2);
	exit (1);
}

int	my_atoi(char *str)
{
	unsigned long long	n;

	n = 0;
	if (*str == '-')
		error("input should include potisive numbers only\n", 0);
	if (*str == '+' && *(str + 1))
		str++;
	while (*str > 47 && *str < 58)
	{
		n = n * 10 + *str - 48;
		str++;
	}
	if (*str)
		error("input should include numbers only\n", 0);
	return (n);
}