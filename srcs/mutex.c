/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 22:35:27 by jihalee           #+#    #+#             */
/*   Updated: 2023/09/06 19:57:44 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	read_holding_forks(t_philo *philo)
{
	int	val_read;

	pthread_mutex_lock(&philo->m_holding_forks);
		val_read = philo->holding_forks;
	pthread_mutex_unlock(&philo->m_holding_forks);
	return (val_read);
}

int	write_holding_forks(t_philo *philo, int to_assign)
{
	pthread_mutex_lock(&philo->m_holding_forks);
		philo->holding_forks = to_assign;
	pthread_mutex_unlock(&philo->m_holding_forks);
	return (to_assign);
}

int	read_stop_now(t_table *table)
{
	int	val_read;

	pthread_mutex_lock(&table->m_stop_now);
		val_read = table->stop_now;
	pthread_mutex_unlock(&table->m_stop_now);
	return (val_read);
}

int	write_stop_now(t_table *table, int to_assign)
{
	pthread_mutex_lock(&table->m_stop_now);
		table->stop_now = to_assign;
	pthread_mutex_unlock(&table->m_stop_now);
	return (to_assign);
}

int	read_state_change(t_philo *philo)
{
	int	val_read;

	pthread_mutex_lock(&philo->m_state_change);
		val_read = philo->state_change;
	pthread_mutex_unlock(&philo->m_state_change);
	return (val_read);
}

int	write_state_change(t_philo *philo, int to_assign)
{
	pthread_mutex_lock(&philo->m_state_change);
		philo->state_change = to_assign;
	pthread_mutex_unlock(&philo->m_state_change);
	return (to_assign);
}

int	read_state(t_philo *philo)
{
	int	val_read;

	pthread_mutex_lock(&philo->m_state);
		val_read = philo->state;
	pthread_mutex_unlock(&philo->m_state);
	return (val_read);
}

int	write_state(t_philo *philo, int to_assign)
{
	pthread_mutex_lock(&philo->m_state);
		philo->state = to_assign;
	pthread_mutex_unlock(&philo->m_state);
	return (to_assign);
}

long	read_crnt_time(t_table *table)
{
	long	val_read;

	pthread_mutex_lock(&table->m_crnt_time);
		val_read = table->crnt_time;
	pthread_mutex_unlock(&table->m_crnt_time);
	return (val_read);
}

long	write_crnt_time(t_table *table, long to_assign)
{
	pthread_mutex_lock(&table->m_crnt_time);
		table->crnt_time = to_assign;
	pthread_mutex_unlock(&table->m_crnt_time);
	return (to_assign);
}

long	read_time_to_die(t_philo *philo)
{
	long	val_read;

	pthread_mutex_lock(&philo->m_time_to_die);
		val_read = philo->time_to_die;
	pthread_mutex_unlock(&philo->m_time_to_die);
	return (val_read);
}

long	write_time_to_die(t_philo *philo, long to_assign)
{
	pthread_mutex_lock(&philo->m_time_to_die);
		philo->time_to_die = to_assign;
	pthread_mutex_unlock(&philo->m_time_to_die);
	return (to_assign);
}
