/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 22:35:27 by jihalee           #+#    #+#             */
/*   Updated: 2023/09/08 23:40:32 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	read_lfork(t_philo *philo)
{
	int	val_read;

	pthread_mutex_lock(&philo->m_lfork);
		val_read = philo->lfork;
	pthread_mutex_unlock(&philo->m_lfork);
	return (val_read);
}

int	write_lfork(t_philo *philo, int to_assign)
{
	pthread_mutex_lock(&philo->m_lfork);
		philo->lfork = to_assign;
	pthread_mutex_unlock(&philo->m_lfork);
	return (to_assign);
}

int	read_rfork(t_philo *philo)
{
	int	val_read;

	pthread_mutex_lock(&philo->m_rfork);
		val_read = philo->rfork;
	pthread_mutex_unlock(&philo->m_rfork);
	return (val_read);
}

int	write_rfork(t_philo *philo, int to_assign)
{
	pthread_mutex_lock(&philo->m_rfork);
		philo->rfork = to_assign;
	pthread_mutex_unlock(&philo->m_rfork);
	return (to_assign);
}
