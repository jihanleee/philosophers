/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 23:38:10 by jihalee           #+#    #+#             */
/*   Updated: 2023/10/21 18:28:53 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	write_stop_now(t_table *table, int to_assign)
{
	pthread_mutex_lock(&table->m_table);
	table->stop_now = to_assign;
	pthread_mutex_unlock(&table->m_table);
	return (to_assign);
}

void	print_death(t_philo *philo, long crnt_time)
{
	pthread_mutex_lock(&philo->table->m_table);
	if (!philo->table->stop_now)
		printf("%ld %d died\n", crnt_time, philo->index);
	philo->table->stop_now = 1;
	pthread_mutex_unlock(&philo->table->m_table);
}

int	increament_n_ate_well(t_table *table)
{
	int	val;

	pthread_mutex_lock(&table->m_table);
	table->n_ate_well++;
	val = table->n_ate_well;
	pthread_mutex_unlock(&table->m_table);
	return (val);
}
