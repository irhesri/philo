/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 03:25:15 by irhesri           #+#    #+#             */
/*   Updated: 2022/07/20 03:25:16 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_sleep(struct timeval start, int time_to_sleep)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	while (gettimestamp(start, now) < time_to_sleep)
	{
		usleep(50);
		gettimeofday(&now, NULL);
	}
}

// result[0] = end.tv_usec / 1000 + end.tv_sec * 1000 ;
// result[1] = start.tv_usec / 1000 + start.tv_sec * 1000 ;
time_t	gettimestamp(struct timeval start, struct timeval end)
{
	time_t	res[2];

	res[0] = (end.tv_sec - start.tv_sec) * 1000;
	res[1] = (end.tv_usec - start.tv_usec) / 1000;
	return (res[0] + res[1]);
}

void	my_print(t_data *data, struct timeval end, int index, short n)
{
	time_t	ts;

	ts = gettimestamp(data->start, end);
	pthread_mutex_lock(&data->print);
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
		pthread_mutex_unlock(&data->print);
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
	return (n);
}
