/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 03:25:18 by irhesri           #+#    #+#             */
/*   Updated: 2022/09/13 11:20:46 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

short	mutex_destroy(t_data *data, t_philo *philo, int index)
{
	int	i;

	i = -1;
	while (++i < index)
	{
		pthread_mutex_destroy((philo + i)->fork);
		pthread_mutex_destroy((philo + i)->meal);
	}
	pthread_mutex_destroy(data->must_eat);
	pthread_mutex_destroy(data->wait);
	pthread_mutex_destroy(data->print);
	return (1);
}

short	init_philos(t_data *data, t_philo *philo)
{
	int		i;
	int		n;

	n = -1;
	if (data->philos_left != -1)
		n = data->n_to_eat;
	i = -1;
	while (++i < data->philos_num)
	{
		(philo + i)->index = i;
		(philo + i)->must_eat = n;
		(philo + i)->fork = malloc(sizeof(pthread_mutex_t));
		(philo + i)->meal = malloc(sizeof(pthread_mutex_t));
		gettimeofday(&(philo + i)->last_meal, NULL);
		if (!(philo + i)->fork || !(philo + i)->meal)
			return (mutex_destroy(data, philo, i));
		if (pthread_mutex_init((philo + i)->fork, NULL))
			return (mutex_destroy(data, philo, i));
		if (pthread_mutex_init((philo + i)->meal, NULL))
		{
			pthread_mutex_destroy((philo + i)->fork);
			return (mutex_destroy(data, philo, i));
		}
	}
	return (0);
}

short	init_mutex(t_data *data)
{
	if (pthread_mutex_init(data->print, NULL))
		return (1);
	if (pthread_mutex_init(data->wait, NULL))
	{
		pthread_mutex_destroy(data->print);
		return (1);
	}
	if (pthread_mutex_init(data->must_eat, NULL))
	{
		pthread_mutex_destroy(data->print);
		pthread_mutex_destroy(data->wait);
		return (1);
	}
	return (0);
}

short	init_data(t_data *data, char **av, int ac)
{
	data->philos_num = my_atoi(av[1]);
	data->time_to_die = my_atoi(av[2]);
	data->time_to_eat = my_atoi(av[3]);
	data->time_to_sleep = my_atoi(av[4]);
	data->philos_left = -1;
	if (data->philos_num < 0 || data->time_to_die < 0
		|| data->time_to_die < 0 || data->time_to_sleep < 0)
		return (1);
	if (ac == 6)
	{
		data->n_to_eat = my_atoi(av[5]);
		if (data->n_to_eat < 0)
			return (1);
		data->philos_left = data->philos_num;
	}
	data->print = malloc(sizeof(pthread_mutex_t));
	data->wait = malloc(sizeof(pthread_mutex_t));
	data->must_eat = malloc(sizeof(pthread_mutex_t));
	data->philo = malloc(sizeof(t_philo) * data->philos_num);
	if (!data->print || !data->wait || !data->must_eat || !data->philo)
		return (printf("allocation error\n"));
	if (init_mutex(data))
		return (1);
	return (init_philos(data, data->philo));
}
