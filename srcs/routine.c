/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 23:38:10 by jihalee           #+#    #+#             */
/*   Updated: 2023/09/12 08:57:56 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	read_stop_now(t_table *table)
{
	bool	result;

	pthread_mutex_lock(&table->m_table);
	result = table->stop_now;
	pthread_mutex_unlock(&table->m_table);
	return (result);
}

bool	write_stop_now(t_table *table, int to_assign)
{
	pthread_mutex_lock(&table->m_table);
	table->stop_now = to_assign;
	pthread_mutex_unlock(&table->m_table);
	return (to_assign);
}

void	*start_routine(void *philo)
{
	int	right;
	int	left;

	left = ((t_philo *)philo)->index;
	right = ((t_philo *)philo)->index + 1;
	if (((t_philo *)philo)->index == ((t_philo *)philo)->table->n_philos - 1)
	{
		right = ((t_philo *)philo)->table->n_philos - 1;
		left = 0;
	}
	if (((t_philo *)philo)->index % 2 == 0)
		msleep(((t_philo *)philo)->table->amnt_time_eat / 8);
	while (!read_stop_now(((t_philo *)philo)->table))
	{
		think((t_philo *)philo, left, right);
		eat_yumyum((t_philo *)philo, left, right);
		sweet_dreams((t_philo *)philo);
	}
	return (0);
}

void	create_threads(t_philo *philos, t_table *table)
{
	int	i;

	gettimeofday(&table->init_tv, NULL);
	i = 0;
	while (i < table->n_philos)
	{
		get_elapsed_time(table);
		pthread_create(&philos[i].id, NULL, start_routine, &philos[i]);
		i++;
	}
	i = 0;
	while (i < table->n_philos)
	{
		pthread_join(philos[i].id, 0);
		i++;
	}
	free(table->forks);
	free(philos);
}

void	eat_yumyum(t_philo *philo, int left, int right)
{
	long	start_time;
	long	crnt_time;

	start_time = get_elapsed_time(philo->table);
	philo->time_to_die = start_time + philo->table->amnt_time_die;
	crnt_time = start_time;
	if (read_stop_now(philo->table) != 1)
		printf("%ld %d is eating\n", crnt_time, philo->index);
	while (crnt_time - start_time < philo->table->amnt_time_eat)
	{
		crnt_time = get_elapsed_time(philo->table);
		if (crnt_time > philo->time_to_die)
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

void	think(t_philo *philo, int left, int right)
{
	long crnt_time;

	if (read_stop_now(philo->table))
		return ;
	printf("%ld %d is thinking\n", get_elapsed_time(philo->table), philo->index);
	if ((philo->time_to_die) > get_elapsed_time(philo->table) + philo->table->amnt_time_eat / 2)
	{
		usleep(philo->table->amnt_time_eat);
	}
	while (philo->table->forks[left].__data.__lock)
	{
		crnt_time = get_elapsed_time(philo->table);
		if (crnt_time > philo->time_to_die)
		{
			write_stop_now(philo->table, 1);
			printf("%ld %d died\n", crnt_time, philo->index);
			break;
		}
		usleep(100);
	}
	pthread_mutex_lock(&philo->table->forks[left]);
	usleep(100);
	printf("%ld %d has taken a fork\n", get_elapsed_time(philo->table), philo->index);
	while (philo->table->forks[right].__data.__lock)
	{
		crnt_time = get_elapsed_time(philo->table);
		if (crnt_time > philo->time_to_die)
		{
			write_stop_now(philo->table, 1);
			printf("%ld %d died\n", crnt_time, philo->index);
			break;
		}
		usleep(100);
	}
	pthread_mutex_lock(&philo->table->forks[right]);
	printf("%ld %d has taken a fork\n", get_elapsed_time(philo->table), philo->index);
}

void	sweet_dreams(t_philo *philo)
{
	long	start_time;
	long	crnt_time;

	if (read_stop_now(philo->table))
		return ;
	start_time = get_elapsed_time(philo->table);
	crnt_time = start_time;
	printf("%ld %d is sleeping\n", crnt_time, philo->index);
	while (crnt_time - start_time < philo->table->amnt_time_sleep)
	{
		crnt_time = get_elapsed_time(philo->table);
		if (crnt_time > philo->time_to_die)
		{
			write_stop_now(philo->table, 1);
			printf("%ld %d died\n", crnt_time, philo->index);
			break;
		}
		usleep(100);
	}
}
