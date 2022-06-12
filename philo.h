#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef	struct s_philo
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	short			stat;
	pthread_t		th;
	suseconds_t		time;
	pthread_mutex_t	mutex;
} t_philo;

typedef	struct s_data
{
	// int		index;
	int		n;
	int		die;
	int		eat;
	int		sleep;
	t_philo	*philo;
} t_data;

int	my_atoi(char *str);

#endif