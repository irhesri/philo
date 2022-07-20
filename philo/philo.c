#include "philo.h"
void	eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->meal);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_unlock(&philo->meal);
	my_print(data, philo->last_meal, philo->index + 1, 2);
	my_print(data, philo->last_meal, philo->index + 1, 3);
	if (philo->must_eat > 0)
	{
		philo->must_eat--;
		if (!philo->must_eat)
		{
			pthread_mutex_lock(&data->must_eat);
			data->philos_left--;
			pthread_mutex_unlock(&data->must_eat);
		}
	}
	my_sleep(philo->last_meal, data->time_to_eat);
}

void	sleep_unlock(t_data *data, t_philo *philo, int x)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	my_print(data, now, philo->index + 1, 4);
	pthread_mutex_unlock(&(data->philo + x)->fork);
	pthread_mutex_unlock(&philo->fork);
	my_sleep(now, data->time_to_sleep);
}

void	*critical_section(void *data)
{
	int			x;
	t_philo		*philo;
	static int	i;
	struct timeval	now;


	pthread_mutex_lock(&((t_data *)data)->wait);
	philo = ((t_data *)data)->philo + i++;
	pthread_mutex_unlock(&((t_data *)data)->wait);
	x = (philo->index + 1) % ((t_data *)data)->philos_num;
	philo->last_meal = ((t_data *)data)->start;
	if (philo->index % 2)
		usleep (500);
	while (1)
	{
		pthread_mutex_lock(&philo->fork);
		gettimeofday(&now, NULL);
		my_print(data, now, philo->index + 1, 1);
		pthread_mutex_lock(&(((t_data *)data)->philo + x)->fork);
		eat(data, philo);
		sleep_unlock(data, philo, x);
		gettimeofday(&now, NULL);
		my_print(data, now, philo->index + 1, 5);
	}
	return (NULL);
}

void	check_for_starvation(t_data *data, t_philo *philo)
{
	int				i;
	struct timeval	now;

	usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&data->must_eat);
		if (!data->philos_left)
			return;
		pthread_mutex_unlock(&data->must_eat);
		i = -1;
		gettimeofday(&now, NULL);
		while (++i < data->philos_num)
		{
			pthread_mutex_lock(&(philo + i)->meal);
			if (gettimestamp((philo + i)->last_meal, now) > data->time_to_die)
			{
				my_print(data, now, i + 1, 6);
				return;
			}
			pthread_mutex_unlock(&(philo + i)->meal);
		}
		usleep(1000);
	}
}

int	main(int ac, char **av)
{
	int			i;
	t_data		*data;
	pthread_t	*th;

	if (ac != 5 && ac != 6)
		return(printf("wrong num of arguments\n"));
	data = init_data(ac, av);
	th = malloc (sizeof(pthread_t) * my_atoi(av[1]));
	if (!data || !data->philo || !th)
		return(printf("allocation error\n"));
	gettimeofday(&data->start, NULL);
	i = -1;
	while (++i < data->philos_num)
		pthread_create(th + i, NULL, critical_section, data);
	check_for_starvation(data, data->philo);
	// while (++i < data->philos_num)
	// {
	// 	pthread_mutex_destroy(&(data->philo + i)->fork);
	// 	pthread_mutex_destroy(&(data->philo + i)->meal);
	// }
	// pthread_mutex_destroy(&data->wait);
	// pthread_mutex_destroy(&data->must_eat);
	// pthread_mutex_destroy(&data->print);

	return (0);
}