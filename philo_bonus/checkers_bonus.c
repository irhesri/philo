/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:03:05 by imane             #+#    #+#             */
/*   Updated: 2022/09/13 12:41:45 by irhesri          ###   ########.fr       */
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

short	check_meals(t_data *data)
{
	int	n;

	n = 0;
	while (1)
	{
		if (sem_wait(data->n_of_meals) == -1)
			error(data, "sem_wait");
		n++;
		if (n == data->philos_num)
			exit (1);
	}
	return (1);
}
