/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 23:38:10 by jihalee           #+#    #+#             */
/*   Updated: 2023/09/13 00:57:06 by jihalee          ###   ########.fr       */
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
	if (!read_stop_now(philo->table))
		printf("%ld %d is eating\n", crnt_time, philo->index);
	philo->eat_count++;
	if (philo->eat_count == philo->table->num_must_eat)
		if (increament_n_ate_well(philo->table) == philo->table->n_philos)
			write_stop_now(philo->table, 1);
	while (crnt_time - start_time < philo->table->amnt_time_eat)
	{
		crnt_time = get_elapsed_time(philo->table);
		if (crnt_time > philo->time_to_die && !read_stop_now(philo->table))
		{
			write_stop_now(philo->table, 1);
			printf("%ld %d died\n", crnt_time, philo->index);
			break ;
		}
		usleep(100);
	}
	pthread_mutex_unlock(&philo->table->forks[left]);
	pthread_mutex_unlock(&philo->table->forks[right]);
}

void	hold_left_fork(t_philo *philo, int left)
{
	long	crnt_time;

	if ((philo->time_to_die) > \
	get_elapsed_time(philo->table) + philo->table->amnt_time_eat / 2)
		usleep(300);
	while (philo->table->forks[left].__data.__lock)
	{
		crnt_time = get_elapsed_time(philo->table);
		if (crnt_time > philo->time_to_die && !read_stop_now(philo->table))
		{
			write_stop_now(philo->table, 1);
			printf("%ld %d died\n", crnt_time, philo->index);
			break ;
		}
		usleep(100);
	}
	pthread_mutex_lock(&philo->table->forks[left]);
	if (!read_stop_now(philo->table))
		printf("%ld %d has taken a fork\n", \
		get_elapsed_time(philo->table), philo->index);
}

void	hold_right_fork(t_philo *philo, int right)
{
	long	crnt_time;

	if ((philo->time_to_die) > \
	get_elapsed_time(philo->table) + philo->table->amnt_time_eat / 2)
		usleep(300);
	while (philo->table->forks[right].__data.__lock)
	{
		crnt_time = get_elapsed_time(philo->table);
		if (crnt_time > philo->time_to_die && !read_stop_now(philo->table))
		{
			write_stop_now(philo->table, 1);
			printf("%ld %d died\n", crnt_time, philo->index);
			break ;
		}
		usleep(100);
	}
	pthread_mutex_lock(&philo->table->forks[right]);
	if (!read_stop_now(philo->table))
		printf("%ld %d has taken a fork\n", \
		get_elapsed_time(philo->table), philo->index);
}

void	think(t_philo *philo)
{
	if (!read_stop_now(philo->table))
		printf("%ld %d is thinking\n", \
		get_elapsed_time(philo->table), philo->index);
}

void	sweet_dreams(t_philo *philo)
{
	long	start_time;
	long	crnt_time;

	start_time = get_elapsed_time(philo->table);
	crnt_time = start_time;
	if (!read_stop_now(philo->table))
		printf("%ld %d is sleeping\n", crnt_time, philo->index);
	while (crnt_time - start_time < philo->table->amnt_time_sleep)
	{
		crnt_time = get_elapsed_time(philo->table);
		if (crnt_time > philo->time_to_die && !read_stop_now(philo->table))
		{
			write_stop_now(philo->table, 1);
			printf("%ld %d died\n", crnt_time, philo->index);
			break ;
		}
		usleep(100);
	}
}