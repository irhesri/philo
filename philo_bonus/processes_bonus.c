/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 08:48:10 by irhesri           #+#    #+#             */
/*   Updated: 2022/08/29 08:56:17 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

short	error(t_data *data, char *str)
{
	sem_wait(data->print);
	printf("%s error\n", str);
	exit (1);
}

void	eat(t_data *data)
{
	my_print(data, data->index + 1, 2);
	my_print(data, data->index + 1, 3);
	pthread_mutex_lock(&data->meal);
	gettimeofday(&(data->last_meal), NULL);
	pthread_mutex_unlock(&data->meal);
	my_sleep(data->time_to_eat);
	if (data->must_eat > 0)
		data->must_eat--;
}

void	*critical_section(void *data_)
{
	t_data	*data;

	data = data_;
	while (gettimestamp(data->start) < 1)
		usleep(10);
	gettimeofday(&data->start, NULL);
	(data->index % 2) && usleep (500);
	while (1)
	{
		sem_wait(data->forks);
		my_print(data, data->index + 1, 1);
		sem_wait(data->forks);
		eat(data);
		sem_post(data->forks);
		sem_post(data->forks);
		if (!data->must_eat)
		{
			pthread_mutex_destroy(&data->meal);
			exit (0);
		}
		my_print(data, data->index + 1, 4);
		my_sleep(data->time_to_sleep);
		my_print(data, data->index + 1, 5);
	}
	return (NULL);
}

void	check_for_starvation(t_data *data)
{
	while (1)
	{
		usleep(50);
		pthread_mutex_lock(&data->meal);
		if (gettimestamp(data->last_meal) > data->time_to_die)
		{
			my_print(data, data->index + 1, 6);
			pthread_mutex_destroy(&data->meal);
			exit (8473);
		}
		pthread_mutex_unlock(&data->meal);
	}
}

void	start_process(t_data *data, int index)
{
	pthread_t	th;

	data->id[index] = fork();
	if (data->id[index] == 0)
	{
		if (pthread_mutex_init(&data->meal, NULL) != 0)
			error(data, "pthread_mutex_init");
		data->index = index;
		data->last_meal = data->start;
		if (pthread_create(&th, NULL, critical_section, data) != 0)
			error(data, "pthread_create");
		check_for_starvation(data);
	}
	if (data->id[index] < 0)
		error(data, "fork");
}
