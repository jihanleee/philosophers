/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_thread_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 23:38:10 by jihalee           #+#    #+#             */
/*   Updated: 2023/09/12 06:12:41 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state_change(t_philo *philo, long crnt_time)
{
	int	state;
	int	stop_now;

	state = read_state(philo);
	stop_now = read_stop_now(philo->table);
	if (state == sleeping && !stop_now)
		printf("%ld %d is sleeping\n", crnt_time, philo->index);
	else if (state == thinking && !stop_now)
		printf("%ld %d is thinking\n", crnt_time, philo->index);
	else if (state == eating && !stop_now)
	{
		printf("%ld %d is eating\n", crnt_time, philo->index);
		(philo->eat_count)++;
	}
	write_state_change(philo, 0);
}

void	print_fork(t_philo *philo)
{
	if (read_stop_now(philo->table))
		return ;
	if (read_lfork(philo))
	{
		printf("%ld %d has taken a fork\n", \
		get_elapsed_time(philo->table), philo->index);
		write_lfork(philo, 0);
	}
	if (read_rfork(philo))
	{
		printf("%ld %d has taken a fork\n", \
		get_elapsed_time(philo->table), philo->index);
		write_rfork(philo, 0);
	}
}

void	check_all_ate_well(t_table *table, t_philo *philos)
{
	int	i;
	int	all_ate_well;

	all_ate_well = 1;
	i = 0;
	while (i < table->n_philos)
	{
		if (table->num_must_eat == -1 \
		|| philos[i].eat_count < table->num_must_eat)
			all_ate_well = 0;
		i++;
	}
	if (all_ate_well)
		write_stop_now(table, 1);
}

void	check_status(t_philo *philos, t_table *table)
{
	int		i;
	long	crnt_time;

	while (!read_stop_now(table))
	{
		i = 0;
		while (i < table->n_philos)
		{
			check_all_ate_well(table, philos);
			print_fork(&philos[i]);
			crnt_time = get_elapsed_time(table);
			if (crnt_time > read_time_to_die(&philos[i]))
			{
				write_stop_now(table, 1);
				printf("%ld %d died\n", crnt_time, i);
				break ;
			}
			else if (read_state_change(&philos[i]))
				print_state_change(&philos[i], crnt_time);
			usleep(100);
			i++;
		}
	}
}
