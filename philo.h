#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef	struct s_philo
{
	int				must_eat;
	// short			stat;
	struct timeval	last_meal;
	pthread_mutex_t	mutex;
} t_philo;

typedef	struct s_data
{
	// int		index;
	int				n;
	struct timeval	start;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	t_philo			*philo;
} t_data;

int		my_atoi(char *str);
short	my_putstr(char *str, int fd);
short	error(char *str, short n);

#endif