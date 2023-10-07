/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:35:34 by about             #+#    #+#             */
/*   Updated: 2023/06/29 14:07:59 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	informations(t_table *table, t_argument *args, int i)
{
	table->id = i + 1;
	table->numberofmeals = 0;
	table->data = args;
	pthread_mutex_init(&table->fork, NULL);
	pthread_mutex_init(&table->lock_health, NULL);
	pthread_mutex_init(&table->meals, NULL);
}

t_table	*initiatable(t_argument *args)
{
	t_table	*table;
	t_table	*first;
	int		i;

	table = malloc(sizeof(t_table));
	first = table;
	i = 0;
	while (i < args->philos)
	{
		informations(table, args, i);
		if (i < args->philos - 1)
		{
			table->rightone = malloc(sizeof(t_table));
			table->rightone->leftone = table;
			table = table->rightone;
		}
		if (i == args->philos - 1)
		{
			first->leftone = table;
			table->rightone = first;
		}
		i++;
	}
	return (first);
}

void	ft_usleep(int time)
{
	struct timeval	start_time;
	struct timeval	current_time;
	int				elapsed_time;

	gettimeofday(&start_time, NULL);
	while (1)
	{
		usleep(100);
		gettimeofday(&current_time, NULL);
		elapsed_time = (current_time.tv_sec - start_time.tv_sec) * 1000
			+ (current_time.tv_usec - start_time.tv_usec) / 1000;
		if (elapsed_time >= time)
			break ;
	}
}

unsigned long	current_time(void)
{
	time_t			time;
	struct timeval	current;

	gettimeofday(&current, NULL);
	time = current.tv_sec * 1000 + current.tv_usec / 1000;
	return (time);
}
