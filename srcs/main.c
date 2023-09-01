#include "philo.h"

long	get_elapsed_time(t_table *table)
{
	t_tv	crnt_time;
	long	ms;

	gettimeofday(&crnt_time, NULL);
	ms = (crnt_time.tv_sec - table->init_tv.tv_sec) * 1000;
	ms += (crnt_time.tv_usec - table->init_tv.tv_usec) / 1000;
	table->crnt_time = ms;
	return (ms);
}

void	print_state_change(t_table *table, t_philo *philo)
{
	if (philo->left_fork)
	{
		printf("%ld %d has taken a fork\n", table->crnt_time, philo->index);
		philo->left_fork = 0;
	}
	if (philo->right_fork)
	{
		printf("%ld %d has taken a fork\n", table->crnt_time, philo->index);
		philo->right_fork = 0;
	}
	if (philo->state == sleeping)
		printf("%ld %d is sleeping\n", table->crnt_time, philo->index);
	if (philo->state == thinking)
		printf("%ld %d is thinking\n", table->crnt_time, philo->index);
	if (philo->state == eating)
	{
		printf("%ld %d is eating\n", table->crnt_time, philo->index);
		(philo->eat_count)++;
	}
	philo->state_change = 0;
}

void *start_routine(void *philo)
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
	while (!((t_philo *)philo)->table->stop_now)
	{
		think((t_philo *)philo, left, right);
		eat_yumyum((t_philo *)philo, left, right);
		sweet_dreams((t_philo *)philo);
	}
	return (0);
}

void	eat_yumyum(t_philo *philo, int left, int right)
{
	long	end_time;
	int		index;
	int		n;

	index = philo->index;
	n = philo->table->n_philos;
	philo->right_fork = 1;
	philo->left_fork = 1;
	philo->table->both_available[index] = 0;
	end_time = philo->table->crnt_time + philo->table->amnt_time_eat;
	philo->state = eating;
	philo->state_change = 1;
	philo->time_to_die = philo->table->crnt_time + philo->table->amnt_time_die;
	while (!philo->table->stop_now \
		&& philo->table->crnt_time < end_time)
		usleep(1000);
	pthread_mutex_unlock(&philo->table->forks[left]);
	pthread_mutex_unlock(&philo->table->forks[right]);
}

void	think(t_philo *philo, int left, int right)
{
	int		n;
	int		index;
	bool	*both_available;
	t_mutex	*forks;

	index = philo->index;
	n = philo->table->n_philos;
	both_available = philo->table->both_available;
	forks = philo->table->forks;
	philo->state = thinking;
	philo->state_change = 1;
	pthread_mutex_lock(&philo->table->forks[left]);
	pthread_mutex_lock(&philo->table->forks[right]);
}

void	sweet_dreams(t_philo *philo)
{
	long	end_time;

	philo->state = sleeping;
	philo->state_change = 1;
	end_time = philo->table->crnt_time + philo->table->amnt_time_sleep;
	while (!philo->table->stop_now \
			&& philo->table->crnt_time < end_time)
		usleep(1000);
}

void	check_status(t_philo *philos, t_table *table)
{
	int		i;
	bool	all_ate_well;

	while (!table->stop_now)
	{
		all_ate_well = (get_elapsed_time(table), 1);
		i = 0;
		while (i < table->n_philos)
		{
			if (table->crnt_time > philos[i].time_to_die)
			{
				table->stop_now = 1;
				printf("%ld %d died\n", table->crnt_time, i);
				break ;
			}
			else if (philos[i].state_change || philos[i].left_fork || philos[i].right_fork)
				print_state_change(table, &philos[i]);
			if (table->num_must_eat == -1 || philos[i].eat_count < table->num_must_eat)
				all_ate_well = 0;
			i++;
		}
		if (all_ate_well)
			table->stop_now = 1;
		usleep(1000);
	}
}

void	create_threads(t_philo *philos, t_table *table)
{
	int	i;

	gettimeofday(&table->init_tv, NULL);
	i = 0;
	while (i < table->n_philos)
	{
		get_elapsed_time(table);
		philos[i].time_to_die = table->amnt_time_die;
		pthread_create(&philos[i].id, NULL, start_routine, &philos[i]);
		i++;
	}
	check_status(philos, table);
	i = 0;
	while (i < table->n_philos)
	{
		pthread_join(philos[i].id, 0);
		i++;
	}
	free(table->forks);
	free(table->both_available);
	free(philos);
}

void	init_vars(t_table *table, t_philo **philos, char argc, char **argv)
{
	int		i;

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
	table->both_available = (bool *)ft_calloc(table->n_philos, sizeof (bool));
	i = 0;
	while (i < table->n_philos)
	{
		pthread_mutex_init(&(table->forks[i]), NULL);
		(*philos)[i].index = i;
		(*philos)[i].table = table;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philos;

	if (argc != 5 && argc != 6)
	{
		write(2, "input error\n", 12);
		return (1);
	}
	init_vars(&table, &philos, argc, argv);
	create_threads(philos, &table);
	return (0);
}

/* bool	are_vars_valid(char **argv)
{
	//should i check????!;_;
} */
