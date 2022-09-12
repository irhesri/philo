/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 08:52:05 by imane             #+#    #+#             */
/*   Updated: 2022/09/12 02:42:29 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

char	*sem_name(int n)
{
	int		size;
	char	*name;

	size = int_size(n);
	size += 4;
	name = malloc(size + 1);
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
