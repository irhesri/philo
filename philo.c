#include "philo.h"

t_data	*initialise(int ac, char **av)
{
	int		i;
	int		n;
	t_philo	*philo;
	t_data	*data;

	data = malloc(sizeof(t_data)); //*********** pro
	data->n = my_atoi(av[1]);
	data->die = my_atoi(av[2]);
	data->eat = my_atoi(av[3]);
	data->sleep = my_atoi(av[4]);
	philo = malloc(sizeof(t_data) * (data->n));//******
	//protection
	n = (ac == 6) * my_atoi(av[5]) - 1 * (ac != 6);
	i = -1;
	while (++i < data->n)
	{
		(philo + i)->time_to_die = data->die;
		(philo + i)->time_to_eat = data->eat;
		(philo + i)->time_to_sleep = data->sleep;
		(philo + i)->must_eat = n;
		(philo + i)->stat = 0;
		// (philo + i)->time = -1;
		pthread_mutex_init(&((philo + i)->mutex), NULL);
	}
	return(data);
}

void	*critical_section(void *data)
{
	struct timeval	now;
	static int		n;
	t_data			*d;
	int				i;
	int				x;

	d = data;
	i = n++;
	gettimeofday(&now, NULL);
	(d->philo + i)->time = now.tv_usec;
	while (1)
	{
		pthread_mutex_lock(&((d->philo + i)->mutex)); //******************
		pthread_mutex_lock(&((d->philo + (i + 1) % d->n)->mutex)); //*****
		x = -1;
		while (x < d->eat)
		{
			gettimeofday(&now, NULL);
			x = now.tv_usec - (d->philo + i)->time;
		}
		pthread_mutex_unlock(&((d->philo + i)->mutex)); //******************
		pthread_mutex_unlock(&((d->philo + (i + 1) % d->n)->mutex)); //*****
		
		x = -1;
		while (x < d->sleep)
		{
			gettimeofday(&now, NULL);
			x = now.tv_usec - (d->philo + i)->time;
		}
	}	
	return(NULL);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		i;


	data = initialise(ac, av);
	i = -1;
	while (++i < data->n)
	{
	
		pthread_create(&((data->philo + i)->th), NULL, critical_section, (void *)data);
	}
	i = -1;
	while (++i < data->n)
		pthread_join((data->philo + i)->th, NULL);
}