/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 03:25:18 by irhesri           #+#    #+#             */
/*   Updated: 2022/08/14 15:16:39 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	destroy_mutex()
// {
// 	if (n - 6)
// }

void	*free_data(t_data *data)
{
	pthread_mutex_destroy(data->print);
	pthread_mutex_destroy(data->wait);
	pthread_mutex_destroy(data->must_eat);
	free (data->print);
	free (data->wait);
	free (data->must_eat);
	free (data);
}

void	*free_philo(t_philo *philo, int i)
{
	int	n;

	n = -1;
	while (++n <= i)
	{
		pthread_mutex_destroy((philo + n)->fork);
		pthread_mutex_destroy((philo + n)->meal);
		free ((philo + n)->fork);
		free ((philo + n)->meal);
	}
	free (philo);
	return (NULL);
}

t_philo	*init_philos(t_data *data, char **av)
{
	int		i;
	int		n;
	int		error;
	t_philo	*philo;

	error = 0;
	philo = malloc(sizeof(t_philo) * data->philos_num);
	if (!philo)
		return (NULL);
	n = -1;
	if (data->philos_left != -1)
		n = my_atoi(av[5]);
	i = -1;
	while (!error && ++i < data->philos_num)
	{
		(philo + i)->index = i;
		(philo + i)->must_eat = n;
		(philo + i)->fork = malloc(sizeof(pthread_mutex_t));
		(philo + i)->meal = malloc(sizeof(pthread_mutex_t));
		if (!(philo + i)->fork || !(philo + i)->meal)
			return (error_case_free(data, philo, i));
		pthread_mutex_init((philo + i)->fork, NULL);
		pthread_mutex_init((philo + i)->meal, NULL);
		
	}
	return (philo);
}

t_data	*init_data(int ac, char **av)
{
	int		error;
	t_data	*data;

	error = 0;
	data = (t_data *) malloc(sizeof(t_data));
	if (!data)
		return (data);
	data->philos_num = my_atoi(av[1]);
	data->time_to_die = my_atoi(av[2]);
	data->time_to_eat = my_atoi(av[3]);
	data->time_to_sleep = my_atoi(av[4]);
	data->philos_left = -1;
	if (ac == 6)
		data->philos_left = data->philos_num;
	data->print = malloc(sizeof(pthread_mutex_t));
	data->wait = malloc(sizeof(pthread_mutex_t));
	data->must_eat = malloc(sizeof(pthread_mutex_t));
	// if (!data->print || !data->wait || !data->must_eat)
	// 	return (error_case_free(data, NULL, -42));
	error -= (pthread_mutex_init(data->wait, NULL) != 0);
	error -= (pthread_mutex_init(data->print, NULL) != 0) * 2;
	error -= (pthread_mutex_init(data->must_eat, NULL) != 0) * 6;
	// if (error)
	// 	return (error_case_free(data, NULL, error)); 
	data->philo = init_philos(data, av);
	// if (!data->philo)
	// 	return (NULL);
	return (data);
}

