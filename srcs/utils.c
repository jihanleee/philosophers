/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 23:38:10 by jihalee           #+#    #+#             */
/*   Updated: 2023/09/12 06:33:20 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_elapsed_time(t_table *table)
{
	t_tv	crnt_time;
	long	ms;

	gettimeofday(&crnt_time, NULL);
	ms = (crnt_time.tv_sec - table->init_tv.tv_sec) * 1000;
	ms += (crnt_time.tv_usec - table->init_tv.tv_usec) / 1000;
	return (ms);
}

void	init_philos(t_table *table, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		pthread_mutex_init(&(table->forks[i]), NULL);
		(*philos)[i].time_to_die = table->amnt_time_die;
		(*philos)[i].index = i;
		(*philos)[i].table = table;
		i++;
	}
}

void	init_vars(t_table *table, t_philo **philos, char argc, char **argv)
{
	table->stop_now = 0;
	table->n_philos = ft_atol(argv[1]);
	table->amnt_time_die = ft_atol(argv[2]);
	table->amnt_time_eat = ft_atol(argv[3]);
	table->amnt_time_sleep = ft_atol(argv[4]);
	table->num_must_eat = -1;
	if (argc == 6)
		table->num_must_eat = ft_atol(argv[5]);
	*philos = (t_philo *)ft_calloc(table->n_philos, sizeof (t_philo));
	table->forks = (t_mutex *)ft_calloc(table->n_philos, sizeof (t_mutex));
	pthread_mutex_init(&table->m_table, NULL);
	init_philos(table, philos);
}

bool	are_args_valid(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	msleep(long ms)
{
	usleep(ms * 1000);
}
