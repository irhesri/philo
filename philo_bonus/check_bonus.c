/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:42:00 by imane             #+#    #+#             */
/*   Updated: 2022/08/27 01:05:26 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_on_meals(t_data *data, int sig)
{
	static t_data	*d;

	if (data || !d)
	{
		d = data;
		return ;
	}
	if (sig == SIGUSR1 && d->philos_left > 0)
		d->philos_left--;
	if (!d->philos_left)
		end_process(0);
}

void	sig_call(int sig)
{
	check_on_meals(NULL, sig);
}

void	check_on_philos(t_data *data)
{
	*(data->id) = fork();
	if (*(data->id) < 0)
		error("fork error\n", -1);
	if (*(data->id) == 0)
	{
		signal(SIGUSR1, sig_call);
		signal(SIGUSR2, end_process);
		while (1)
			;
	}
}
