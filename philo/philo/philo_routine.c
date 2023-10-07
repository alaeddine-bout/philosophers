/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:37:35 by about             #+#    #+#             */
/*   Updated: 2023/06/29 14:09:27 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dourthing(t_table *table)
{
	pthread_mutex_lock(&table->fork);
	ft_display("[%lu] philo %d has taken a fork\n", table);
	pthread_mutex_lock(&table->rightone->fork);
	ft_display("[%lu] philo %d has taken a fork\n", table);
	pthread_mutex_lock(&table->lock_health);
	table->health = current_time();
	pthread_mutex_unlock(&table->lock_health);
	ft_display("[%lu] philo %d is eating\n", table);
	pthread_mutex_lock(&table->meals);
	table->numberofmeals++;
	pthread_mutex_unlock(&table->meals);
	ft_usleep(table->data->timetoeat);
	pthread_mutex_unlock(&table->fork);
	pthread_mutex_unlock(&table->rightone->fork);
	ft_display("[%lu] philo %d is sleeping\n", table);
	ft_usleep(table->data->timetosleep);
	ft_display("[%lu] philo %d is thinking\n", table);
}

void	ft_display(const char *action, t_table *table)
{
	pthread_mutex_lock(&table->data->lock_print);
	printf(action, current_time() - table->data->timeofstarting, table->id);
	pthread_mutex_unlock(&table->data->lock_print);
}

void	*routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	pthread_mutex_lock(&table->lock_health);
	table->health = table->data->timeofstarting;
	pthread_mutex_unlock(&table->lock_health);
	while (1)
		dourthing(table);
}

void	the_creation(pthread_t *philo, t_table *table, t_argument *args,
		t_table *temp)
{
	int	i;

	i = 0;
	while (i < args->philos)
	{
		pthread_create(&philo[i], NULL, routine, temp);
		pthread_detach(philo[i]);
		temp = temp->rightone->rightone;
		i += 2;
	}
	temp = table->rightone;
	usleep(300);
	i = 1;
	while (i < args->philos)
	{
		pthread_create(&philo[i], NULL, routine, temp);
		pthread_detach(philo[i]);
		temp = temp->rightone->rightone;
		i += 2;
	}
}
