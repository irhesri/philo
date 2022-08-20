/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 03:25:15 by irhesri           #+#    #+#             */
/*   Updated: 2022/08/20 14:09:19 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	exit (1);
}
