/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 03:25:24 by irhesri           #+#    #+#             */
/*   Updated: 2022/08/14 17:40:13 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_data *data, t_philo *philo)
{
	my_print(data, philo->index + 1, 2);
	my_print(data, philo->index + 1, 3);
	pthread_mutex_lock(philo->meal);
	gettimeofday(&(philo->last_meal), NULL);
	pthread_mutex_unlock(philo->meal);
	my_sleep(data->time_to_sleep);
	if (philo->must_eat > 0 && !(--(philo->must_eat)))
	{
		pthread_mutex_lock(data->must_eat);
		data->philos_left--;
		pthread_mutex_unlock(data->must_eat);
	}
	pthread_mutex_unlock(philo->fork);
}

void	*critical_section(void *data_)
{
	int				x;
	t_data			*data;
	t_philo			*philo;
	static int		index;

	data = data_;
	pthread_mutex_lock(data->wait);
	philo = data->philo + index++;
	pthread_mutex_unlock(data->wait);
	x = (philo->index + 1) % data->philos_num;
	philo->last_meal = data->start;
	(philo->index % 2 == 1) && usleep (500);
	while (1)
	{
		pthread_mutex_lock(philo->fork);
		my_print(data, philo->index + 1, 1);
		pthread_mutex_lock((data->philo + x)->fork);
		eat(data, philo);
		pthread_mutex_unlock((data->philo + x)->fork);
		my_print(data, philo->index + 1, 4);
		my_sleep(data->time_to_sleep);
		my_print(data, philo->index + 1, 5);
	}
	return (NULL);
}

void	check_for_starvation(t_data *data, t_philo *philo)
{
	int	i;

	usleep(50);
	while (1)
	{
		pthread_mutex_lock(data->must_eat);
		if (!data->philos_left)
			return ;
		pthread_mutex_unlock(data->must_eat);
		i = -1;
		while (++i < data->philos_num)
		{
			pthread_mutex_lock((philo + i)->meal);
			if (gettimestamp((philo + i)->last_meal) > data->time_to_die)
			{
				my_print(data, i + 1, 6);
				return ;
			}
			pthread_mutex_unlock((philo + i)->meal);
		}
		usleep(50);
	}
}

int	main(int ac, char **av)
{
	int			i;
	t_data		*data;
	pthread_t	*th;

	if (ac != 5 && ac != 6)
		return (printf("wrong num of arguments\n"));
	data = init_data(ac, av);
	th = malloc (sizeof(pthread_t) * my_atoi(av[1]));
	if (!data || !data->philo || !th)
		return (printf("allocation error\n"));
	gettimeofday(&data->start, NULL);
	i = -1;
	while (++i < data->philos_num)
		pthread_create(th + i, NULL, critical_section, data);
	check_for_starvation(data, data->philo);
	//	destroy mutexes
	return (0);
}
