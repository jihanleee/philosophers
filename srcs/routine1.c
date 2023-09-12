/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 23:38:10 by jihalee           #+#    #+#             */
/*   Updated: 2023/09/13 00:43:17 by jihalee          ###   ########.fr       */
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
	if (((t_philo *)philo)->index % 2 == 0)
		msleep(((t_philo *)philo)->table->amnt_time_eat / 5);
	while (!read_stop_now(((t_philo *)philo)->table))
	{
		hold_left_fork((t_philo *)philo, left);
		hold_right_fork((t_philo *)philo, right);
		eat_yumyum((t_philo *)philo, left, right);
		sweet_dreams((t_philo *)philo);
		think((t_philo *)philo);
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
		usleep(10);
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
