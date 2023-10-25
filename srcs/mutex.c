/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 23:38:10 by jihalee           #+#    #+#             */
/*   Updated: 2023/10/25 17:14:48 by jihalee          ###   ########.fr       */
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

bool	read_stop_now(t_table *table)
{
	bool	value;

	pthread_mutex_lock(&table->m_table);
	value = table->stop_now;
	pthread_mutex_unlock(&table->m_table);
	return (value);
}

void	print_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->m_print);
	if (!read_stop_now(philo->table))
		printf("%ld %d is dead\n", get_elapsed_time(philo->table), philo->index);
	write_stop_now(philo->table, 1);
	pthread_mutex_unlock(&philo->table->m_print);
}

void	print_msg(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->m_print);
	if (!read_stop_now(philo->table))
		printf("%ld %d %s\n", get_elapsed_time(philo->table), philo->index, msg);
	pthread_mutex_unlock(&philo->table->m_print);
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
