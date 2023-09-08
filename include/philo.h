/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 13:28:40 by jihalee           #+#    #+#             */
/*   Updated: 2023/09/08 23:53:35 by jihalee          ###   ########.fr       */
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

typedef enum e_state
{
	thinking,
	sleeping,
	eating
}			t_state;

typedef struct s_table
{
	t_mutex		*forks;
	t_tv		init_tv;
	bool		stop_now;
	t_mutex		m_stop_now;
	int			n_philos;
	long		amnt_time_die;
	long		amnt_time_eat;
	long		amnt_time_sleep;
	int			num_must_eat;
	long		crnt_time;
	t_mutex		m_crnt_time;
}				t_table;

typedef struct s_philo
{
	t_table		*table;
	int			state;
	t_mutex		m_state;
	int			index;
	t_thread	id;
	long		time_to_die;
	t_mutex		m_time_to_die;
	bool		lfork;
	t_mutex		m_lfork;
	bool		rfork;
	t_mutex		m_rfork;
	bool		is_dead;
	bool		state_change;
	t_mutex		m_state_change;
	int			eat_count;
}				t_philo;

int		write_lfork(t_philo *philo, int to_assign);
int		read_lfork(t_philo *philo);
int		write_rfork(t_philo *philo, int to_assign);
int		read_rfork(t_philo *philo);
long	write_time_to_die(t_philo *philo, long to_assign);
long	read_time_to_die(t_philo *philo);
long	write_crnt_time(t_table *table, long to_assign);
long	read_crnt_time(t_table *table);
int		write_state(t_philo *philo, int to_assign);
int		read_state(t_philo *philo);
int		write_state_change(t_philo *philo, int to_assign);
int		read_state_change(t_philo *philo);
int		read_stop_now(t_table *table);
int		write_stop_now(t_table *table, int value_to_assign);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atol(const char *nptr);
void	sweet_dreams(t_philo *philo);
void	think(t_philo *philo, int left, int right);
void	eat_yumyum(t_philo *philo, int left, int right);
void	check_all_ate_well(t_table *table, t_philo *philos);
bool	are_args_valid(char **argv);
void	init_vars(t_table *table, t_philo **philos, char argc, char **argv);
long	get_elapsed_time(t_table *table);
void	create_threads(t_philo *philos, t_table *table);
void	check_status(t_philo *philos, t_table *table);

#endif
