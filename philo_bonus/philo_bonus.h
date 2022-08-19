
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
	pid_t			*id;/****************/
	sem_t			*print;
	sem_t			**fork;
	struct timeval	last_meal;
	pthread_mutex_t	*meal;
	struct timeval	start; /*************/
}	t_data;


void	init_data(t_data *data, char **av, int ac);
void	number_of_meal(t_data *data);

void	check(t_data *data, int sig);
void	sig_call(int sig);
// pid_t	check_for_meals(t_data *data);
void	check_philos(t_data *data);



int		my_atoi(char *str);
void	my_print(t_data *data, int index, short n);
void	my_sleep(int time_to_sleep);
time_t	gettimestamp(struct timeval start);
char	*my_name(int n);
short	error(char *str, pid_t id);

#endif