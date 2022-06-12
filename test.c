#include "philo.h"

int			x = 2;
pthread_mutex_t	mutex[2];

void	*routine()
{
	static int n;
	int k;

	k = n++;
	printf("---> %d HERE \n", k);
	pthread_mutex_lock(mutex + k);
	pthread_mutex_lock(mutex + ((k + 1) % x));
	printf("---> %d is eating \n", k);

	sleep(500);

	// printf("\n");
	pthread_mutex_unlock(mutex + k);
	pthread_mutex_unlock(mutex + ((k + 1) % x));
	printf("---> %d is sleeping \n", k);
	sleep(500);
	printf("---> %d is thinking \n", k);

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
	i = -1;
	while (++i < x)
	{
		pthread_join(th[i], NULL);
	}
	
}