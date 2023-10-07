/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 22:36:35 by about             #+#    #+#             */
/*   Updated: 2023/06/29 14:09:45 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\f' || c == '\r'
		|| c == '\v');
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	result;

	result = 0;
	sign = 1;
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - 48);
		if (result > 9223372036854775807 && sign == 1)
			return (-1);
		if (result > 9223372036854775807 && sign == -1)
			return (0);
	}
	return (result * sign);
}

int	valid_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				printf("Something shouldn't be there !");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	initiargs(char **philo, t_argument *args)
{
	if (!args)
		return (0);
	args->philos = ft_atoi(philo[1]);
	if (args->philos <= 0)
		return (0);
	args->timetodie = ft_atoi(philo[2]);
	args->timetoeat = ft_atoi(philo[3]);
	args->timetosleep = ft_atoi(philo[4]);
	pthread_mutex_init(&args->lock_print, NULL);
	if (args->timetodie < 60 || args->timetosleep < 60 || args->timetoeat < 60)
		return (0);
	if (philo[5])
	{
		args->each_philo_must_eat = ft_atoi(philo[5]);
		if (args->each_philo_must_eat == 0)
		{
			printf("Invalid number of meals\n");
			return (0);
		}
	}
	else
		args->each_philo_must_eat = -1;
	return (1);
}
