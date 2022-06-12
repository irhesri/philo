#include "philo.h"

int			x = 30;
pthread_mutex_t	mutex[30];

void	*routine()
{
	static int n;
	int k;

	k = n++;
	pthread_mutex_lock(mutex + k);
	pthread_mutex_lock(mutex + ((k + 1) % x));
	printf("----->start : %d\n", k);

	usleep(30);

	// printf("\n");
	printf("->end : %d\n", k);
	pthread_mutex_unlock(mutex + k);
	pthread_mutex_unlock(mutex + ((k + 1) % x));
	return (NULL);
}

int	main()
{
	pthread_t	th[x];
	int 		i = -1;

	while (++i < x)
		pthread_mutex_init(mutex + i, NULL);
	i = 0;
	while (i < x)
	{
		pthread_create(th + i, NULL, &routine, NULL);
		// usleep(5);
		i++;
	}
	// usleep(5);
	// i = 1;
	// while (i < 10)
	// {
	// 	pthread_create(th + i, NULL, &routine, NULL);
	// 	i += 2;
	// }

	i = -1;
	while (++i < x)
	{
		pthread_join(th[i], NULL);
	}
	
}