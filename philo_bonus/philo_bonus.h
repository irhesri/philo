/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 11:51:49 by irhesri           #+#    #+#             */
/*   Updated: 2022/08/30 13:40:37 by imane            ###   ########.fr       */
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
# include <signal.h>

typedef struct s_data
{
	int				index;
	int				philos_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	pid_t			*id;
	sem_t			*print;
	sem_t			*forks;
	sem_t			*n_of_meals;
	struct timeval	last_meal;
	struct timeval	start;
	pthread_mutex_t	meal;
}	t_data;

int		my_atoi(char *str);
void	my_sleep(int time_to_sleep);
void	my_print(t_data *data, int index, short n);
void	start_process(t_data *data, int index);
short	error(t_data *data, char *str);
void	end_processes(t_data *data, pid_t id);
void	check_for_starvation(t_data *data);
void	*check_meals(void *data);
time_t	gettimestamp(struct timeval start);

#endif
