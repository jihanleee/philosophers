/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 13:28:40 by jihalee           #+#    #+#             */
/*   Updated: 2023/08/29 00:53:22 by jihalee          ###   ########.fr       */
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

/*
typedef struct s_
{

}				t_
*/

typedef pthread_mutex_t	t_mutex;
typedef pthread_t	t_thread;
typedef suseconds_t	t_useconds;
typedef struct timeval t_tv;

typedef enum e_state
{
	thinking,
	sleeping,
	holding_forks,
	eating
}			t_state;

typedef struct s_table
{
	t_mutex		*forks;
	bool		*both_available;
	t_tv		init_tv;
	bool		stop_now;
	int			n_philos;
	long		amnt_time_die;
	long		amnt_time_eat;
	long		amnt_time_sleep;
	int			num_must_eat;
	long		crnt_time;
}				t_table;

typedef struct s_philo
{
	t_table		*table;
	int			state;
	int			index;
	t_thread	id;
	long		time_to_die;
	bool		left_fork;
	bool		right_fork;
	bool		is_dead;
	bool		state_change;
	int			eat_count;
}				t_philo;

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atol(const char *nptr);
void	sweet_dreams(t_philo *philo);
void	think(t_philo *philo);
void	eat_yumyum(t_philo *philo);
#endif