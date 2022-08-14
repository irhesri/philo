/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 03:25:18 by irhesri           #+#    #+#             */
/*   Updated: 2022/08/14 16:52:49 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// void	destroy_mutex()
// {
// 	if (n - 6)
// }

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
	// data->print = malloc(sizeof(pthread_mutex_t));
	// data->wait = malloc(sizeof(pthread_mutex_t));
	// data->must_eat = malloc(sizeof(pthread_mutex_t));
	// if (!data->print || !data->wait || !data->must_eat)
	// 	return (error_case_free(data, NULL, -42));
	// error -= (pthread_mutex_init(data->wait, NULL) != 0);
	// error -= (pthread_mutex_init(data->print, NULL) != 0) * 2;
	// error -= (pthread_mutex_init(data->must_eat, NULL) != 0) * 6;
	// if (error)
	// 	return (error_case_free(data, NULL, error)); 
	// data->philo = init_philos(data, av);
	// if (!data->philo)
	// 	return (NULL);
	return (data);
}

