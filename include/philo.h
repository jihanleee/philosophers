/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 13:28:40 by jihalee           #+#    #+#             */
/*   Updated: 2023/09/13 00:42:17 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;
typedef suseconds_t		t_useconds;
typedef struct timeval	t_tv;

typedef struct s_table
{
	t_mutex		*forks;
	t_tv		init_tv;
	bool		stop_now;
	t_mutex		m_table;
	int			n_philos;
	long		amnt_time_die;
	long		amnt_time_eat;
	long		amnt_time_sleep;
	int			num_must_eat;
	int			n_ate_well;
}				t_table;

typedef struct s_philo
{
	t_table		*table;
	t_thread	id;
	int			state;
	int			index;
	long		time_to_die;
	bool		is_dead;
	bool		state_change;
	int			eat_count;
}				t_philo;

int		increament_n_ate_well(t_table *table);
bool	read_stop_now(t_table *table);
bool	write_stop_now(t_table *table, int value_to_assign);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atol(const char *nptr);
void	sweet_dreams(t_philo *philo);
void	think(t_philo *philo);
void	hold_left_fork(t_philo *philo, int left);
void	hold_right_fork(t_philo *philo, int right);
void	eat_yumyum(t_philo *philo, int left, int right);
void	check_all_ate_well(t_table *table, t_philo *philos);
bool	are_args_valid(char **argv);
void	init_vars(t_table *table, t_philo **philos, char argc, char **argv);
long	get_elapsed_time(t_table *table);
void	create_threads(t_philo *philos, t_table *table);
void	check_status(t_philo *philos, t_table *table);
void	msleep(long ms);

#endif
