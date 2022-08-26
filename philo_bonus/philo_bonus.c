/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 11:23:29 by imane             #+#    #+#             */
/*   Updated: 2022/08/23 13:50:21 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	int		i;
	t_data	*data;

	if (ac != 5 && ac != 6)
		return (error("wrong num of arguments\n", -1));
	data = malloc(sizeof(t_data));
	(!data) && error("allocation error\n", -1);
	init_data(data, av, ac);
	if (data->must_eat > 0)
		data->philos_left = data->philos_num;
	check_on_philos(data);
	gettimeofday(&data->start, NULL);
	i = -1;
	while (++i < data->philos_num)
		start_process(data, i);
	i = -1;
	waitpid(data->id[++i], NULL, 0);
	while (++i < (data->philos_num + 1))
		kill(data->id[i], SIGUSR2);
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (0);
}
