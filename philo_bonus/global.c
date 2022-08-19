/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:42:00 by imane             #+#    #+#             */
/*   Updated: 2022/08/19 19:21:42 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check(t_data *data, int sig)
{
	int				i;
	static t_data	*d;

	if (data)
	{
		d = data;
		return ;
	}
	if (!d)
		return ;
	if (sig == SIGUSR1 && d->philos_left > 0)
		d->philos_left--;
	if (!d->philos_left || sig == SIGUSR2)
	{
		i = -1;
		while (++i < d->philos_num)
			kill(d->id[i + 1], SIGUSR2);
		exit (0);
	}
}

void	sig_call(int sig)
{
	check(NULL, sig);
}

void	check_philos(t_data *data)
{
	*(data->id) = fork();
	if (*(data->id) < 0)
		error("fork error\n", -1);
	if (*(data->id) == 0)
	{
		signal(SIGUSR1, sig_call);
		signal(SIGUSR2, sig_call);
		while (1);		
	}
}