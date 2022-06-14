#include "philo.h"

time_t	get_timestamp(struct timeval start, struct timeval end)
{
	time_t			result[2];

	result[0] = (end.tv_sec - start.tv_sec) * 1000 ;
	// result[0] = end.tv_usec / 1000 + end.tv_sec * 1000 ;
	// result[1] = start.tv_usec / 1000 + start.tv_sec * 1000 ;
	result[1] = (end.tv_usec - start.tv_usec) / 1000;
	return (result[0] + result[1]);
}

t_data	*initialise(int ac, char **av)
{
	int		i;
	int		n;
	t_philo	*philo;
	t_data	*data;

	data = malloc(sizeof(t_data));
	!(data) && error("allocation error\n", 0);
	data->n = my_atoi(av[1]);
	data->time_to_die = my_atoi(av[2]);
	data->time_to_eat = my_atoi(av[3]);
	data->time_to_sleep = my_atoi(av[4]);
	philo = malloc(sizeof(t_philo) * (data->n));
	!(philo) && error("allocation error\n", 0);
	n = -1;
	if (ac == 6)
		n = my_atoi(av[5]);
	data->must_eat = n * (n == -1) + (unsigned long long)(n * data->n * (n != -1));
	i = -1;
	while (++i < data->n)
	{
		(philo + i)->must_eat = n;
		(pthread_mutex_init(&((philo + i)->mutex), NULL) != 0) && error(NULL, 4);
	}
	data->philo = philo;
	return (data);
}

struct timeval	my_sleep(struct timeval start, time_t to_sleep/*, int i*/)
{
	struct timeval	now;
	time_t			x;

	usleep((3 * to_sleep) / 4);
	to_sleep += (start.tv_sec * 1000 + start.tv_usec / 1000);
	x = -1;
	while (x < to_sleep)
	{
		(gettimeofday(&now, NULL) != 0) && error(NULL, 3);
		x = (now.tv_sec * 1000 + now.tv_usec / 1000);
		usleep (50);
	}
	// if (x == to_sleep)
	// {
	// 	usleep (1000);
	// 	(gettimeofday(&now, NULL) != 0) && error(NULL, 3);
	// }
	return (now);
}

// (i % 2) && (usleep(100) != 0) && error("usleep() failed\n", 0);
// (usleep(d->time_to_eat * 1000) != 0) && error("usleep() failed\n", 0);
// (usleep(d->time_to_sleep * 1000) != 0) && error("usleep() failed\n", 0);
void	*critical_section(void *data)
{
	static int		n;
	t_philo			*philo;
	t_data			*d;
	struct timeval	now;
	int				i[2];

	d = data;
	philo = d->philo;
	i[0] = n++;
	i[1] = (i[0] + 1) % d->n;
	while (d->must_eat)
	{	
		(pthread_mutex_lock(&((philo + i[0])->mutex)) != 0) && error(NULL, 1);
		(gettimeofday(&now, NULL) != 0) && error(NULL, 3);
		printf(" % 8ld % 4d   has taken a right fork 🍴 \n", get_timestamp(d->start, now), (*i) + 1);
		(pthread_mutex_lock(&((philo + i[1])->mutex)) != 0) && error(NULL, 1);
		(gettimeofday(&now, NULL) != 0) && error(NULL, 3);
		printf(" % 8ld % 4d   has taken a left fork  🍴 \n", get_timestamp(d->start, now), (*i) + 1);
		(gettimeofday(&((philo + *i)->last_meal), NULL) != 0) && error("", 3);
		printf("\033[34;1m % 8ld % 4d   is eating\033[0m   🍽️ \n", get_timestamp(d->start, (philo + (*i))->last_meal), (*i) + 1);
		d->must_eat -= ((philo + *i)->must_eat > 0);
		if (!d->must_eat)
			exit (0);				// exit threads
		(philo + *i)->must_eat -= ((philo + *i)->must_eat > 0);
		now = my_sleep((philo + *i)->last_meal, d->time_to_eat);
		// (gettimeofday(&now, NULL) != 0) && error(NULL, 3);
		(pthread_mutex_unlock(&((philo + *i)->mutex)) != 0) && error(NULL, 2);
		(pthread_mutex_unlock(&((philo + i[1])->mutex)) != 0) && error(NULL, 2);
		printf("\033[0;1m % 8ld % 4d   is sleeping\033[0m 😴 \n", get_timestamp(d->start, now), (*i) + 1);
		now = my_sleep(now, d->time_to_sleep);
		// (gettimeofday(&now, NULL) != 0) && error(NULL, 3);
		printf("\033[2;1m % 8ld % 4d   is thinking\033[0m 💭 \n", get_timestamp(d->start, now), (*i) + 1);
	}
	return (NULL);
}

void	*check_for_starvation(void *data)
{
	t_data	*d;
	time_t	x;
	int		i;
	struct timeval	now;

	d = (t_data *)data;
	while (1)
	{
		i = -1;
		(gettimeofday(&now, NULL) != 0) && error(NULL, 3);
		while (++i < d->n)
		{
			x = get_timestamp((d->philo + i)->last_meal, now);
			if (d->philo->must_eat && x > d->time_to_die)
			{
				printf("\033[31;1m % 8ld % 4d   is dead!\033[0m    💀 \n", x, i + 1);
				exit (0);				// exit threads
			}
		}
		(usleep(1000) != 0) && error("usleep() failed\n", 0);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data			*data;
	pthread_t		*th;
	int				i;

	ac != 5 && ac != 6 && error("wrong number of arguments\n", 0);
	data = initialise(ac, av);
	th = malloc(sizeof(pthread_t) * (data->n + 1));
	!(th) && error("allocation error\n", 0);
	i = -1;
	(gettimeofday(&data->start, NULL) != 0) && error(NULL, 3);
	while (++i < data->n)
	{
		(data->philo + i)->last_meal = data->start;
		pthread_create(th + i, NULL, critical_section, (void *)data);
		(usleep(50) != 0) && error("usleep() failed\n", 0);
	}
	pthread_create(th + data->n, NULL, check_for_starvation, (void *)data);
	i = -1;
	while (++i < data->n)
		pthread_join(th[i], NULL);
}
