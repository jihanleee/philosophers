/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 23:38:10 by jihalee           #+#    #+#             */
/*   Updated: 2023/09/08 23:52:27 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (((t_philo *)philo)->table->n_philos == 1)
	{
		((t_philo *)philo)->state_change = 1;
		while (!read_stop_now(((t_philo *)philo)->table))
			usleep(1000);
		return (0);
	}
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
	check_status(philos, table);
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
	long	time_to_die;

	write_state(philo, eating);
	write_state_change(philo, 1);
	usleep(100);
	time_to_die = get_elapsed_time(philo->table) + philo->table->amnt_time_die;
	write_time_to_die(philo, time_to_die);
	usleep(philo->table->amnt_time_eat * 1000);
	pthread_mutex_unlock(&philo->table->forks[left]);
	pthread_mutex_unlock(&philo->table->forks[right]);
}

void	think(t_philo *philo, int left, int right)
{
	write_state(philo, thinking);
	write_state_change(philo, 1);
	usleep(100);
	pthread_mutex_lock(&philo->table->forks[left]);
	write_lfork(philo, 1);
	pthread_mutex_lock(&philo->table->forks[right]);
	write_rfork(philo, 1);
}

void	sweet_dreams(t_philo *philo)
{
	write_state(philo, sleeping);
	write_state_change(philo, 1);
	usleep(100);
	usleep(philo->table->amnt_time_eat * 1000);
}
