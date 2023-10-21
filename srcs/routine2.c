/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 23:38:10 by jihalee           #+#    #+#             */
/*   Updated: 2023/10/21 18:55:25 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_yumyum(t_philo *philo, int left, int right)
{
	long	start_time;
	long	crnt_time;

	start_time = get_elapsed_time(philo->table);
	philo->time_to_die = start_time + philo->table->amnt_time_die;
	crnt_time = start_time;
	if (!philo->table->stop_now)
		printf("%ld %d is eating\n", crnt_time, philo->index);
	philo->eat_count++;
	if (philo->eat_count == philo->table->num_must_eat)
		if (increament_n_ate_well(philo->table) == philo->table->n_philos)
			write_stop_now(philo->table, 1);
	while (crnt_time - start_time < philo->table->amnt_time_eat \
		&& !philo->table->stop_now)
	{
		crnt_time = get_elapsed_time(philo->table);
		if (crnt_time > philo->time_to_die)
			print_death(philo, crnt_time);
		usleep(50);
	}
	pthread_mutex_unlock(&philo->table->forks[left]);
	pthread_mutex_unlock(&philo->table->forks[right]);
}

int	hold_forks(t_philo *philo, int left, int right)
{
	long	crnt_time;

	while ((philo->table->forks[left].__data.__lock || \
		philo->table->forks[right].__data.__lock) \
		|| philo->table->n_philos == 1)
	{
		crnt_time = get_elapsed_time(philo->table);
		if (crnt_time > philo->time_to_die && !philo->table->stop_now)
		{
			print_death(philo, crnt_time);
			return (0);
		}
		usleep(50);
	}
	pthread_mutex_lock(&philo->table->forks[left]);
	if (!philo->table->stop_now)
		printf("%ld %d has taken a fork\n", \
		get_elapsed_time(philo->table), philo->index);
	pthread_mutex_lock(&philo->table->forks[right]);
	if (!philo->table->stop_now)
		printf("%ld %d has taken a fork\n", \
		get_elapsed_time(philo->table), philo->index);
	return (1);
}

void	think(t_philo *philo)
{
	if (!philo->table->stop_now)
		printf("%ld %d is thinking\n", \
		get_elapsed_time(philo->table), philo->index);
}

void	sweet_dreams(t_philo *philo)
{
	long	start_time;
	long	crnt_time;

	start_time = get_elapsed_time(philo->table);
	crnt_time = start_time;
	if (!philo->table->stop_now)
		printf("%ld %d is sleeping\n", crnt_time, philo->index);
	while (crnt_time - start_time <= philo->table->amnt_time_sleep \
		&& !philo->table->stop_now)
	{
		crnt_time = get_elapsed_time(philo->table);
		if (crnt_time > philo->time_to_die && !philo->table->stop_now)
		{
			print_death(philo, crnt_time);
			break ;
		}
		usleep(50);
	}
}
