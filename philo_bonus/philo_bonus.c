/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 11:51:06 by irhesri           #+#    #+#             */
/*   Updated: 2022/08/28 12:38:24 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_data	*init_data(char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit (printf("allocation error\n"));
	data->philos_num = my_atoi(av[1]);
	data->time_to_die = my_atoi(av[2]);
	data->time_to_eat = my_atoi(av[3]);
	data->time_to_sleep = my_atoi(av[4]);
	data->must_eat = my_atoi(av[5]);
	data->id = malloc(sizeof(pid_t) * data->philos_num);
	if (!data->id)
		exit (printf("allocation error\n"));
	sem_unlink("print");
	sem_unlink("forks");
	data->print = sem_open("print", O_CREAT, 0644, 1);
	data->forks = sem_open("forks", O_CREAT, 0644, data->philos_num);
	if (data->print == SEM_FAILED || data->forks == SEM_FAILED)
		exit (printf("sem_open error\n"));
	return (data);
}

void	end_processes(t_data *data, pid_t id)
{
	int	i;

	if (id > 0)
	{
		i = -1;
		while (++i < data->philos_num)
		{
			if (id != data->id[i])
				kill(data->id[i], SIGKILL);
		}
	}
	sem_close(data->forks);
	sem_close(data->print);
}

int	main(int ac, char **av)
{
	int		i;
	pid_t	pid;
	t_data	*data;

	if (ac != 5 && ac != 6)
		return (printf("wrong num of arguments\n"));
	data = init_data(av);
	i = -1;
	gettimeofday(&data->start, NULL);
	while (++i < data->philos_num)
		start_process(data, i);
	while (1)
	{
		pid = waitpid(-1, &i, 0);
		if (pid < 0 || i > 0)
			break ;
	}
	end_processes(data, pid);
	return (0);
}
