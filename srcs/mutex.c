/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 23:38:10 by jihalee           #+#    #+#             */
/*   Updated: 2023/09/13 00:57:39 by jihalee          ###   ########.fr       */
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

int	increament_n_ate_well(t_table *table)
{
	int	val;

	pthread_mutex_lock(&table->m_table);
	table->n_ate_well++;
	val = table->n_ate_well;
	pthread_mutex_unlock(&table->m_table);
	return (val);
}
