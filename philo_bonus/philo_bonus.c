/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 11:51:06 by irhesri           #+#    #+#             */
/*   Updated: 2022/09/15 12:03:44 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_sem(t_data *data)
{
	sem_unlink("print");
	sem_unlink("forks");
	sem_unlink("number_of_meals");
	data->print = sem_open("print", O_CREAT, 0644, 1);
	data->forks = sem_open("forks", O_CREAT, 0644, data->philos_num);
	data->n_of_meals = sem_open("number_of_meals", O_CREAT, 0644, 0);
	if (data->print == SEM_FAILED || data->forks == SEM_FAILED
		|| data->n_of_meals == SEM_FAILED)
		exit (printf("sem_open error\n"));
}

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
	data->id = malloc(sizeof(pid_t) * (data->philos_num + 1));
	if (!data->id)
		exit (printf("allocation error\n"));
	init_sem(data);
	return (data);
}

void	close_sem(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->n_of_meals);
}

int	main(int ac, char **av)
{
	int			i;
	pid_t		pid;
	t_data		*data;

	if (ac != 5 && ac != 6)
		return (printf("wrong num of arguments\n"));
	data = init_data(av);
	if (ac == 6)
	{
		pid = fork();
		(pid < 0) && error(data, "sem_post");
		(!pid) && check_meals(data);
		data->id[data->philos_num] = pid;
	}
	i = -1;
	gettimeofday(&data->start, NULL);
	while (++i < data->philos_num)
		start_process(data, i);
	pid = waitpid(-1, &i, 0);
	end_processes(data, pid);
	close_sem(data);
	return (0);
}
