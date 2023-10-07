/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:59:14 by about             #+#    #+#             */
/*   Updated: 2023/06/29 14:27:16 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	checkifdead(t_table *table)
{
	unsigned long	mytime;
	int				status;

	status = 0;
	pthread_mutex_lock(&table->lock_health);
	mytime = (current_time() - table->health);
	if (mytime >= (unsigned long)table->data->timetodie)
		status = 1;
	pthread_mutex_unlock(&table->lock_health);
	return (status);
}

void	deathxphilo(t_table *table)
{
	while (1)
	{
		if (table->data->each_philo_must_eat != -1 && ft_meals(table))
		{
			pthread_mutex_lock(&table->data->lock_print);
			return ;
		}
		if (checkifdead(table))
		{
			pthread_mutex_lock(&table->data->lock_print);
			printf("[%lu] philo %d died\n", current_time()
				- table->data->timeofstarting, table->id);
			break ;
		}
		table = table->rightone;
	}
}

int	ft_meals(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data->philos)
	{
		pthread_mutex_lock(&table->meals);
		if (table->numberofmeals < table->data->each_philo_must_eat)
		{
			pthread_mutex_unlock(&table->meals);
			return (0);
		}
		pthread_mutex_unlock(&table->meals);
		table = table->rightone;
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_argument	*args;
	t_table		*table;
	t_table		*temp;
	pthread_t	*philo;

	if (ac == 5 || ac == 6)
	{
		args = malloc(sizeof(t_argument));
		if (valid_args(av) == 0)
			return (1);
		if (initiargs(av, args) == 0)
			return (1);
		args->timeofstarting = current_time();
		table = initiatable(args);
		philo = malloc(sizeof(int) * args->philos);
		temp = table;
		the_creation(philo, table, args, temp);
		deathxphilo(table);
	}
	else
	{
		printf("wrong number of arguments\n");
		return (1);
	}
}
