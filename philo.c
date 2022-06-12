#include "philo.h"

t_data	*initialise(int ac, char **av)
{
	int		i;
	int		n;
	t_philo	*philo;
	t_data	*data;

	data = malloc(sizeof(t_data)); //*********** pro
	data->n = my_atoi(av[1]);
	data->time_to_die = my_atoi(av[2]);
	data->time_to_eat = my_atoi(av[3]) * 1000;
	data->time_to_sleep = my_atoi(av[4]) * 1000;
	philo = malloc(sizeof(t_philo) * (data->n));//******
	//protection
	n = -1;
	if (ac == 6)
		n = my_atoi(av[5]);
	i = -1;
	while (++i < data->n)
	{
		(philo + i)->must_eat = n;
		pthread_mutex_init(&((philo + i)->mutex), NULL);
	}
	data->philo = philo;
	return(data);
}

void	*critical_section(void *data)
{
	struct timeval	now;
	static int		n;
	t_data			*d;
	t_philo			*philo;
	int				i;

	d = data;
	philo = d->philo;
	i = n++;
	gettimeofday(&now, NULL);
	(philo + i)->last_meal = now.tv_usec / 1000;
	if (i % 2)
		usleep(1000);
	while ((philo + i)->must_eat)
	{	
		pthread_mutex_lock(&((philo + i)->mutex)); //******************
		pthread_mutex_lock(&((philo + (i + 1) % d->n)->mutex)); //*****
		printf("---> %d is eating \n", i + 1);
		gettimeofday(&now, NULL);
		(philo + i)->last_meal = now.tv_usec / 1000;
		usleep(d->time_to_eat);
		(philo + i)->must_eat -= ((philo + i)->must_eat > 0);
		pthread_mutex_unlock(&((philo + i)->mutex)); //******************
		pthread_mutex_unlock(&((philo + (i + 1) % d->n)->mutex)); //*****
		printf("---> %d is sleeping \n", i + 1);
		usleep(d->time_to_sleep);
		printf("---> %d is thinking \n", i + 1);
	}	
	return(NULL);
}


void	*check_for_starvation(void *d)
{
	struct timeval	now;
	suseconds_t		x;
	t_philo			*philo;
	t_data			*data;
	int				i;

	data = (t_data *)d;
	philo = data->philo;
	while (1)
	{
		gettimeofday(&now, NULL);
		i = -1;
		while (++i < data->n)
		{
			// printf("%ld - ", now.tv_usec / 1000);
			// printf("%ld - ", (philo + i)->last_meal);

			x = ((now.tv_usec / 1000) - (philo + i)->last_meal);
			// printf("%ld\n", x);
			if (philo->must_eat && x > data->time_to_die)
			{
				printf("-- %ld ---> %d is dead \n", x, i + 1);
				exit (0);
			}
		}
		usleep(3000);
	}
	return(NULL);
}

int	main(int ac, char **av)
{
	t_data		*data;
	pthread_t	*th;
	int			i;

	//protect ac
	data = initialise(ac, av);
	th = malloc(sizeof(pthread_t) * (data->n + 1)); //***************
	i = -1;
	while (++i < data->n)
		pthread_create(th + i, NULL, critical_section, (void *)data);
	pthread_create(th + data->n, NULL, check_for_starvation, (void *)data);
	i = -1;
	while (++i < data->n)
		pthread_join(th[i], NULL);
}