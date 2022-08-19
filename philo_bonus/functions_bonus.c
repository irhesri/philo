/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 03:25:15 by irhesri           #+#    #+#             */
/*   Updated: 2022/08/19 18:46:35 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	my_sleep(int time_to_sleep)
{
	struct timeval	now;
	struct timeval start;
	
	gettimeofday(&start, NULL);
	usleep(100);
	while (gettimestamp(start) < time_to_sleep)
	{
		usleep(100);
		gettimeofday(&now, NULL);
	}
}

time_t	gettimestamp(struct timeval start)
{
	time_t			res[2];
	struct timeval	now;

	gettimeofday(&now, NULL);
	res[0] = now.tv_usec / 1000 + now.tv_sec * 1000;
	res[1] = start.tv_usec / 1000 + start.tv_sec * 1000 ;
	// res[0] = (end.tv_sec - start.tv_sec) * 1000;
	// res[1] = (end.tv_usec - start.tv_usec) / 1000;
	return (res[0] - res[1]);
}

void	my_print(t_data *data, int index, short n)
{
	time_t	ts;

	ts = gettimestamp(data->start);
	sem_wait(data->print);
	if (n == 1)
		printf(" % 8ld % 4d   has taken a right fork 🍴 \n", ts, index);
	if (n == 2)
		printf(" % 8ld % 4d   has taken a left fork  🍴 \n", ts, index);
	if (n == 3)
		printf("\033[34;1m % 8ld % 4d   is eating\033[0m   🍽️ \n", ts, index);
	if (n == 4)
		printf("\033[0;1m % 8ld % 4d   is sleeping\033[0m 😴 \n", ts, index);
	if (n == 5)
		printf("\033[2;1m % 8ld % 4d   is thinking\033[0m 💭 \n", ts, index);
	if (n == 6)
		printf("\033[31;1m % 8ld % 4d   died!\033[0m    💀 \n", ts, index);
	if (n != 6)
		sem_post(data->print);
}

int	my_atoi(char *str)
{
	unsigned long long	n;

	n = 0;
	if (*str == '-')
		exit(printf("input should include potisive numbers only\n"));
	if (*str == '+' && *(str + 1))
		str++;
	while (*str > 47 && *str < 58)
	{
		n = n * 10 + *str - 48;
		str++;
	}
	if (*str)
		exit(printf("input should include numbers only\n"));
	if (!n)
		exit(printf("input should only include numbers bigger than zero\n"));
	return (n);
}

static int	int_size(int n)
{
	int	i;

	i = 0;
	while (!i || n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*my_name(int n)
{
	int		size;
	char	*name;

	size = int_size(n);
	size += 4;
	name = malloc(sizeof(size + 1));
	name[size] = '\0';
	name[0] = 's';
	name[1] = 'e';
	name[2] = 'm';
	name[3] = '_';
	while (--size > 3)
	{
		name[size] = (n % 10) + 48;
		n /= 10;
	}
	return (name);
}

short	error(char *str, pid_t id)
{
	printf("%s\n", str);
	if (id > 0)
		kill(SIGUSR2, id);
	exit (errno);
}