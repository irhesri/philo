
#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>

typedef struct s_data
{
	int				philos_num;
	int				philos_left;
	int				must_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	struct timeval	start;
}	t_data;

int		my_atoi(char *str);
void	my_print(t_data *data, int index, short n);
void	my_sleep(int time_to_sleep);
t_data	*init_data(int ac, char **av);
time_t	gettimestamp(struct timeval start);

#endif