/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:48:42 by imane             #+#    #+#             */
/*   Updated: 2022/08/30 13:33:42 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

short	error(t_data *data, char *str)
{
	if (sem_wait(data->print) == -1)
		error(data, "sem_wait");
	printf("%s error\n", str);
	exit (1);
}

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
	if (sem_wait(data->print) == -1)
		error(data, "sem_wait");
	if (n == 1)
		printf(" % 8ld % 4d   has taken a fork \n", ts, index);
	if (n == 2)
		printf(" % 8ld % 4d   has taken a fork \n", ts, index);
	if (n == 3)
		printf("\033[34;1m % 8ld % 4d   is eating\033[0m \n", ts, index);
	if (n == 4)
		printf("\033[0;1m % 8ld % 4d   is sleeping\033[0m \n", ts, index);
	if (n == 5)
		printf("\033[2;1m % 8ld % 4d   is thinking\033[0m  \n", ts, index);
	if (n == 6)
		printf("\033[31;1m % 8ld % 4d   died\033[0m    \n", ts, index);
	if (n != 6)
	{
		if (sem_post(data->print) == -1)
			error(data, "sem_post");
	}
}

int	my_atoi(char *str)
{
	unsigned long long	n;

	n = 0;
	if (!str)
		return (-1);
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
