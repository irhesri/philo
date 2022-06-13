#include "philo.h"

time_t	get_timestamp(struct timeval start)
{
	struct timeval	now;
	time_t			result[2];

	(gettimeofday(&now, NULL) != 0) && error(NULL, 3);
	result[0] = (now.tv_sec - start.tv_sec) * 1000 ;
	result[1] = (now.tv_usec - start.tv_usec) / 1000;
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
	i = -1;
	while (++i < data->n)
	{
		(philo + i)->must_eat = n;
		(pthread_mutex_init(&((philo + i)->mutex), NULL) != 0) && error(NULL, 4);
	}
	data->philo = philo;
	return (data);
}

// void	my_sleep(time_t to_sleep)
// {
// 	struct timeval	now;

// 	(gettimeofday(&now, NULL) != 0) && error(NULL, 3);
// 	usleep (to_sleep / 2 * 1000);
// 	// to_sleep -= 1000;
// 	// printf("%d\n", );
// 	while (get_timestamp(now) < to_sleep);
// 		// printf("%ld\n", get_timestamp(now));

// }

// (i % 2) && (usleep(100) != 0) && error("usleep() failed\n", 0);
void	*critical_section(void *data)
{
	static int		n;
	t_philo			*philo;
	t_data			*d;
	int				i;
	int				x;

	d = data;
	philo = d->philo;
	i = n++;
	x = (i + 1) % d->n;
	while ((philo + i)->must_eat)
	{	
		(pthread_mutex_lock(&((philo + i)->mutex)) != 0) && error(NULL, 1);
		(pthread_mutex_lock(&((philo + x)->mutex)) != 0) && error(NULL, 1);
		printf("%ld %d is eating 🍽️ \n", get_timestamp(d->start), i + 1);
		(gettimeofday(&((philo + i)->last_meal), NULL) != 0) && error(NULL, 3);
		// (usleep(d->time_to_eat * 1000) != 0) && error("usleep() failed\n", 0);
		// my_sleep(d->time_to_eat);
		(philo + i)->must_eat -= ((philo + i)->must_eat > 0);
		(pthread_mutex_unlock(&((philo + i)->mutex)) != 0) && error(NULL, 2);
		(pthread_mutex_unlock(&((philo + x)->mutex)) != 0) && error(NULL, 2);
		printf("%ld %d is sleeping 😴 \n", get_timestamp(d->start), i + 1);
		// (usleep(d->time_to_sleep * 1000) != 0) && error("usleep() failed\n", 0);
		// my_sleep(d->time_to_sleep);
		printf("%ld %d is thinking 💭 \n", get_timestamp(d->start), i + 1);
	}	
	return (NULL);
}

void	*check_for_starvation(void *d)
{
	t_philo	*philo;
	t_data	*data;
	time_t	x;
	int		i;

	data = (t_data *)d;
	philo = data->philo;
	while (1)
	{
		i = -1;
		while (++i < data->n)
		{
			x = get_timestamp((philo + i)->last_meal);
			if (philo->must_eat && x > data->time_to_die)
			{
				printf("\033[31;1m-- %ld ---> %d is dead\033[0m 💀 \n", x, i + 1);
				exit (0);
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
		(usleep(100) != 0) && error("usleep() failed\n", 0);
	}
	pthread_create(th + data->n, NULL, check_for_starvation, (void *)data);
	i = -1;
	while (++i < data->n)
		pthread_join(th[i], NULL);
}
