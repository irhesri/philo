/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 03:25:28 by irhesri           #+#    #+#             */
/*   Updated: 2022/08/14 13:33:15 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				index;
	int				must_eat;
	struct timeval	last_meal;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*meal;
}	t_philo;

typedef struct s_data
{
	int				philos_num;
	int				philos_left;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	t_philo			*philo;
	struct timeval	start;
	pthread_mutex_t	*print;
	pthread_mutex_t	*wait;
	pthread_mutex_t	*must_eat;
}	t_data;

int		my_atoi(char *str);
void	my_print(t_data *data, int index, short n);
void	my_sleep(int time_to_sleep);
// void	my_sleep(struct timeval start, int time_to_sleep);
t_data	*init_data(int ac, char **av);
time_t	gettimestamp(struct timeval start);

#endif