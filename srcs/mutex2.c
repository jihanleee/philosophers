/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 22:35:27 by jihalee           #+#    #+#             */
/*   Updated: 2023/09/08 23:40:25 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
