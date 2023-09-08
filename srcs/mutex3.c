/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 22:35:27 by jihalee           #+#    #+#             */
/*   Updated: 2023/09/08 23:40:21 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
