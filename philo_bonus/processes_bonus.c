/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 08:48:10 by irhesri           #+#    #+#             */
/*   Updated: 2022/09/10 10:12:32 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat(t_data *data)
{
	if (sem_wait(data->forks) == -1)
		error(data, "sem_wait");
	my_print(data, data->index + 1, 1);
	if (sem_wait(data->forks) == -1)
		error(data, "sem_wait");
	my_print(data, data->index + 1, 2);
	my_print(data, data->index + 1, 3);
	sem_wait(*(data->meal + data->index));
	gettimeofday(&(data->last_meal), NULL);
	sem_post(*(data->meal + data->index));
	my_sleep(data->time_to_eat);
	if (data->must_eat > 0)
		data->must_eat--;
	if (sem_post(data->forks) == -1)
		error(data, "sem_post");
	if (sem_post(data->forks) == -1)
		error(data, "sem_post");
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
		eat(data);
		if (!data->must_eat)
		{
			if (sem_post(data->n_of_meals) == -1)
				error(data, "sem_post");
			data->must_eat = -1;
		}
		my_print(data, data->index + 1, 4);
		my_sleep(data->time_to_sleep);
		my_print(data, data->index + 1, 5);
	}
	return (NULL);
}

void	start_process(t_data *data, int index)
{
	pthread_t	th;

	data->id[index] = fork();
	if (data->id[index] == 0)
	{
		data->index = index;
		data->last_meal = data->start;
		if (pthread_create(&th, NULL, critical_section, data) != 0)
			error(data, "pthread_create");
		check_for_starvation(data);
	}
	if (data->id[index] < 0)
		error(data, "fork");
}

void	end_processes(t_data *data, pid_t id)
{
	int	i;

	i = -1;
	while (++i < data->philos_num)
	{
		if (id != data->id[i])
			kill(data->id[i], SIGKILL);
	}
}
