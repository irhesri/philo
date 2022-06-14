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
	struct timeval	last_meal;
	pthread_mutex_t	mutex;
} t_philo;

typedef	struct s_data
{
	unsigned long long	must_eat;
	struct timeval		start;
	t_philo				*philo;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	int					n;
} t_data;

int		my_atoi(char *str);
short	my_putstr(char *str, int fd);
short	error(char *str, short n);

#endif