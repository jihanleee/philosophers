/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 23:38:10 by jihalee           #+#    #+#             */
/*   Updated: 2023/10/25 17:18:56 by jihalee          ###   ########.fr       */
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
	print_msg("is eating", philo);
	philo->eat_count++;
	if (philo->eat_count == philo->table->num_must_eat)
		if (increament_n_ate_well(philo->table) == philo->table->n_philos)
			write_stop_now(philo->table, 1);
	while (crnt_time - start_time < philo->table->amnt_time_eat \
		&& !read_stop_now(philo->table))
	{
		crnt_time = get_elapsed_time(philo->table);
		if (crnt_time > philo->time_to_die)
			print_death(philo);
		usleep(50);
	}
	pthread_mutex_unlock(&philo->table->forks[left]);
	pthread_mutex_unlock(&philo->table->forks[right]);
}

int	hold_forks(t_philo *philo, int left, int right)
{
	long	crnt_time;

	while (philo->table->n_philos == 1 || \
		(philo->table->forks[left].__data.__lock || \
		philo->table->forks[right].__data.__lock))
	{
		crnt_time = get_elapsed_time(philo->table);
		if (crnt_time > philo->time_to_die && !read_stop_now(philo->table))
		{
			print_death(philo);
			return (0);
		}
		usleep(50);
	}
	pthread_mutex_lock(&philo->table->forks[left]);
	pthread_mutex_lock(&philo->table->forks[right]);
	print_msg("has taken a fork", philo);
	print_msg("has taken a fork", philo);
	return (1);
}

void	think(t_philo *philo)
{
	print_msg("is thinking", philo);
}

void	sweet_dreams(t_philo *philo)
{
	long	start_time;
	long	crnt_time;

	start_time = get_elapsed_time(philo->table);
	crnt_time = start_time;
	print_msg("is sleeping", philo);
	while (crnt_time - start_time <= philo->table->amnt_time_sleep \
		&& !read_stop_now(philo->table))
	{
		crnt_time = get_elapsed_time(philo->table);
		if (crnt_time > philo->time_to_die && !read_stop_now(philo->table))
		{
			print_death(philo);
			break ;
		}
		usleep(50);
	}
}
