/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:03:05 by imane             #+#    #+#             */
/*   Updated: 2022/09/12 02:45:49 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_for_starvation(t_data *data)
{
	while (1)
	{
		usleep(50);
		sem_wait(*(data->meal + data->index));
		if (gettimestamp(data->last_meal) > data->time_to_die)
		{
			my_print(data, data->index + 1, 6);
			exit (8473);
		}
		sem_post(*(data->meal + data->index));
	}
}

void	*check_meals(void *data_)
{
	int			n;
	t_data		*data;

	data = data_;
	while (1)
	{
		if (sem_wait(data->n_of_meals) == -1)
			error(data, "sem_wait");
		n++;
		if (n == data->philos_num)
		{
			end_processes(data, -1);
			break ;
		}
	}
	return (NULL);
}
