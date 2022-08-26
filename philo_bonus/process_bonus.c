/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:48:28 by imane             #+#    #+#             */
/*   Updated: 2022/08/23 13:52:24 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat(t_data *data)
{
	my_print(data, data->index + 1, 2);
	my_print(data, data->index + 1, 3);
	pthread_mutex_lock(data->meal);
	gettimeofday(&(data->last_meal), NULL);
	pthread_mutex_unlock(data->meal);
	my_sleep(data->time_to_eat);
	if (data->must_eat > 0)
		data->must_eat--;
	if (!data->must_eat)
		kill(*(data->id), SIGUSR1);
}

void	*critical_section(void *data_)
{
	int		x;
	t_data	*data;

	data = data_;
	x = (data->index + 1) % data->philos_num;
	(data->index % 2 == 1) && usleep (500);
	while (1)
	{
		sem_wait(*(data->fork + data->index));
		my_print(data, data->index + 1, 1);
		sem_wait(*(data->fork + x));
		eat(data);
		sem_post(*(data->fork + x));
		sem_post(*(data->fork + data->index));
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
		pthread_mutex_lock(data->meal);
		if (gettimestamp(data->last_meal) > data->time_to_die)
		{
			my_print(data, data->index + 1, 6);
			kill(*(data->id), SIGUSR2);
			return ;
		}
		pthread_mutex_unlock(data->meal);
	}
}

void	end_process(int sig)
{
	exit (0);
}

void	start_process(t_data *data, int index)
{
	int			i;
	pthread_t	th;

	data->id[index + 1] = fork();
	if (data->id[index + 1] < 0)
		error("fork error\n", *(data->id));
	if (data->id[index + 1] == 0)
	{
		data->last_meal = data->start;
		data->index = index;
		signal(SIGUSR2, end_process);
		(pthread_create(&th, NULL, critical_section, data));
		check_for_starvation(data);
		while (1)
			;
	}
}
