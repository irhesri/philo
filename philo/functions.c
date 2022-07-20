#include "philo.h"

void	my_sleep(struct timeval	start, int time_to_sleep)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	while (gettimestamp(start, now) < time_to_sleep)
	{
		usleep(50);
		gettimeofday(&now, NULL);
	}
}

time_t	gettimestamp(struct timeval start, struct timeval end)
{
	time_t	res[2];

	res[0] = (end.tv_sec - start.tv_sec) * 1000;
	res[1] = (end.tv_usec - start.tv_usec) / 1000;
	return (res[0] + res[1]);
}

void	my_print(t_data *data, struct timeval end, int index, short n)
{
	time_t	ts;

	ts = gettimestamp(data->start, end);
	pthread_mutex_lock(&data->print);
	if (n == 1)
		printf("%ld   %d   right fork\n", ts, index);
	if (n == 2)
		printf("%ld   %d   left fork\n", ts, index);
	if (n == 3)
		printf("%ld   %d   is eating\n", ts, index);	
	if (n == 4)
		printf("%ld   %d   is sleeping\n", ts, index);
	if (n == 5)
		printf("%ld   %d   is thinking\n", ts, index);
	if (n == 6)
		printf("%ld   %d   died\n", ts, index);
	if (n != 6)
		pthread_mutex_unlock(&data->print);
}

int	my_atoi(char *str)
{
	unsigned long long	n;

	n = 0;
	if (*str == '-')
		exit(printf("input should include potisive numbers only\n"));
	if (*str == '+' && *(str + 1))
		str++;
	while (*str > 47 && *str < 58)
	{
		n = n * 10 + *str - 48;
		str++;
	}
	if (*str)
		exit(printf("input should include numbers only\n"));
	return (n);
}