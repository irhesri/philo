/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 03:25:15 by irhesri           #+#    #+#             */
/*   Updated: 2022/09/12 02:49:44 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_sleep(int time_to_sleep)
{
	struct timeval	now;
	struct timeval	start;

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
	return (res[0] - res[1]);
}

void	my_print(t_data *data, int index, short n)
{
	time_t	ts;

	ts = gettimestamp(data->start);
	pthread_mutex_lock(data->print);
	if (n == 1)
		printf(" % 8ld % 4d   has taken a fork \n", ts, index);
	if (n == 2)
		printf(" % 8ld % 4d   has taken a fork \n", ts, index);
	if (n == 3)
		printf("\033[34;1m % 8ld % 4d   is eating\033[0m \n", ts, index);
	if (n == 4)
		printf("\033[0;1m % 8ld % 4d   is sleeping\033[0m \n", ts, index);
	if (n == 5)
		printf("\033[2;1m % 8ld % 4d   is thinking\033[0m \n", ts, index);
	if (n == 6)
		printf("\033[31;1m % 8ld % 4d   died\033[0m \n", ts, index);
	if (n != 6)
		pthread_mutex_unlock(data->print);
}

int	my_atoi(char *str)
{
	unsigned long long	n;

	n = 0;
	if (*str == '-')
	{
		printf("input should include potisive numbers only\n");
		return (-1);
	}
	if (*str == '+' && *(str + 1))
		str++;
	while (*str > 47 && *str < 58 && n < 2147483647)
	{
		n = n * 10 + *str - 48;
		str++;
	}
	if (*str || !n || n > 2147483647)
	{
		printf("input should include only numbers between zero and max int\n");
		return (-1);
	}
	return (n);
}
