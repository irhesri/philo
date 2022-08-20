/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:29:29 by imane             #+#    #+#             */
/*   Updated: 2022/08/20 14:05:51 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_forks(t_data *data)
{
	int		i;
	char	*str;

	i = -1;
	data->fork = malloc(sizeof(sem_t *) * data->philos_num);
	(!data->fork) && error("allocation error\n", -1);
	while (++i < data->philos_num)
	{
		str = my_name(i);
		(sem_unlink(str) == -1);// && error("sem_unlink error\n", -1);
		*(data->fork + i) = sem_open(str, O_CREAT, 0644, 1);
		(*(data->fork + i) == SEM_FAILED) && error("sem_open error\n", -1);
		free(str);
	}
}

void	init_data(t_data *data, char **av, int ac)
{
	data->philos_num = my_atoi(av[1]);
	data->time_to_die = my_atoi(av[2]);
	data->time_to_eat = my_atoi(av[3]);
	data->time_to_sleep = my_atoi(av[4]);
	data->must_eat = -1;
	if (ac == 6)
		data->must_eat = my_atoi(av[5]);
	data->id = malloc(sizeof(int) * (data->philos_num + 1));
	(!data->id) && error("allocation error\n", -1);
	data->meal = malloc(sizeof(pthread_mutex_t));
	(!data->meal) && error("allocation error\n", -1);
	if (pthread_mutex_init(data->meal, NULL) != 0)
		error("mutex_init error\n", -1);
	(sem_unlink("print") == -1);// && error("sem_unlink error\n", -1);
	data->print = sem_open("print", O_CREAT, 0644, 1);
	(data->print == SEM_FAILED) && error("sem_open error\n", -1);
	init_forks(data);
	check_on_meals(data, 0);
}
