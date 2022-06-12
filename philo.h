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
	suseconds_t		last_meal;
	pthread_mutex_t	mutex;
} t_philo;

typedef	struct s_data
{
	// int		index;
	int				n;
	suseconds_t		time_to_die;
	suseconds_t		time_to_eat;
	suseconds_t		time_to_sleep;
	t_philo			*philo;
} t_data;

int	my_atoi(char *str);

#endif