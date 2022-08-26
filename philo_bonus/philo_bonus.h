/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:51:16 by imane             #+#    #+#             */
/*   Updated: 2022/08/23 13:51:54 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_data
{
	int				index;
	int				philos_num;
	int				philos_left;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	pid_t			*id;
	sem_t			*print;
	sem_t			**fork;
	struct timeval	last_meal;
	pthread_mutex_t	*meal;
	struct timeval	start;
}	t_data;

int		my_atoi(char *str);
char	*my_name(int n);
void	init_data(t_data *data, char **av, int ac);
void	number_of_meal(t_data *data);
void	my_print(t_data *data, int index, short n);
void	my_sleep(int time_to_sleep);
short	error(char *str, pid_t id);
time_t	gettimestamp(struct timeval start);

// PROCESS FUNCTIONS
void	end_process(int sig);
void	start_process(t_data *data, int index);
void	*critical_section(void *data_);
void	check_on_philos(t_data *data);
void	check_on_meals(t_data *data, int sig);

#endif