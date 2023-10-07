/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:51:56 by about             #+#    #+#             */
/*   Updated: 2023/06/29 14:08:33 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_argument
{
	int				philos;
	int				timetodie;
	int				timetoeat;
	int				timetosleep;
	int				each_philo_must_eat;
	pthread_mutex_t	lock_print;
	time_t			timeofstarting;
}					t_argument;

typedef struct s_table
{
	int				id;
	int				numberofmeals;
	pthread_mutex_t	fork;
	pthread_mutex_t	meals;
	pthread_mutex_t	lock_health;
	unsigned long	health;
	struct s_table	*rightone;
	struct s_table	*leftone;
	t_argument		*data;
}					t_table;

int					valid_args(char **av);
int					ft_atoi(const char *str);
int					initiargs(char **philo, t_argument *args);
t_table				*initiatable(t_argument *args);
void				*routine(void *table);
void				the_creation(pthread_t *philo, t_table *table,
						t_argument *args, t_table *temp);
unsigned long		current_time(void);
void				informations(t_table *table, t_argument *args, int i);
void				ft_usleep(int time);
void				deathxphilo(t_table *table);
int					checkifdead(t_table *table);
int					ft_meals(t_table *table);
void				ft_display(const char *action, t_table *table);
void				dourthing(t_table *table);

#endif