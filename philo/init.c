#include "philo.h"

t_philo	*init_philos(t_data *data, char **av)
{
	int		i;
	int		n;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * data->philos_num);
	if (!philo)
		return (philo);
	n = -1;
	if (data->philos_left != -1)
		n = my_atoi(av[5]);
	i = -1;
	while (++i < data->philos_num)
	{
		(philo + i)->index = i;
		(philo + i)->must_eat = n;
		pthread_mutex_init(&(philo + i)->fork, NULL);
		pthread_mutex_init(&(philo + i)->meal, NULL);
	}
	return (philo);
}

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = (t_data *) malloc(sizeof(t_data));
	if (!data)
		return data;
	data->philos_num = my_atoi(av[1]);
	data->time_to_die = my_atoi(av[2]);
	data->time_to_eat = my_atoi(av[3]);
	data->time_to_sleep = my_atoi(av[4]);
	data->philos_left = -1;
	if (ac == 6)
		data->philos_left = data->philos_num;
	pthread_mutex_init(&data->wait, NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->must_eat, NULL);
	data->philo = init_philos(data, av);
	return (data);
}