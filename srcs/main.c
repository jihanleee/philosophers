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

void	print_state_change(t_table *table, t_philo *philo, t_philo *philos, long crnt_time)
{
	int	state;
	int	stop_now;

	state = read_state(philo);
	check_all_ate_well(table, philos);
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
	if (((t_philo *)philo)->table->n_philos == 1)
	{
		((t_philo *)philo)->state_change = 1;
		while (!read_stop_now(((t_philo *)philo)->table))
			usleep(1000);
		return (0);
	}
	while (!read_stop_now(((t_philo *)philo)->table))
	{
		think((t_philo *)philo, left, right);
		eat_yumyum((t_philo *)philo, left, right);
		sweet_dreams((t_philo *)philo);
	}
	return (0);
}

void	eat_yumyum(t_philo *philo, int left, int right)
{
	long	time_to_die;


	write_state(philo, eating);
	write_state_change(philo, 1);
	usleep(100);
	time_to_die = get_elapsed_time(philo->table) + philo->table->amnt_time_die;
	write_time_to_die(philo, time_to_die);
	usleep(philo->table->amnt_time_eat * 1000);
	pthread_mutex_unlock(&philo->table->forks[left]);
	printf("%ld %d has put down lfork\n", get_elapsed_time(philo->table), philo->index);
	pthread_mutex_unlock(&philo->table->forks[right]);
	printf("%ld %d has put down rfork\n", get_elapsed_time(philo->table), philo->index);
}

void	think(t_philo *philo, int left, int right)
{
	write_state(philo, thinking);
	write_state_change(philo, 1);
	usleep(100);//why does this prevent death?
	pthread_mutex_lock(&philo->table->forks[left]);
	printf("%ld %d has taken lfork\n", get_elapsed_time(philo->table), philo->index);
	pthread_mutex_lock(&philo->table->forks[right]);
	printf("%ld %d has taken rfork\n", get_elapsed_time(philo->table), philo->index);
}

void	sweet_dreams(t_philo *philo)
{
	write_state(philo, sleeping);
	write_state_change(philo, 1);
	usleep(100);
	usleep(philo->table->amnt_time_eat * 1000);
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
			crnt_time = get_elapsed_time(table);
			if (crnt_time > read_time_to_die(&philos[i]))
			{
				write_stop_now(table, 1);
				printf("%ld %d died\n", crnt_time, i);
				break ;
			}
			else if (read_state_change(&philos[i]))
				print_state_change(table, &philos[i], philos, crnt_time);
			i++;
		}
		usleep(100);
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
	pthread_mutex_init(&table->m_stop_now, NULL);
	pthread_mutex_init(&table->m_crnt_time, NULL);
	i = 0;
	while (i < table->n_philos)
	{
		pthread_mutex_init(&(table->forks[i]), NULL);
		pthread_mutex_init(&((*philos)[i].m_state), NULL);
		(*philos)[i].time_to_die = table->amnt_time_die;
		(*philos)[i].index = i;
		(*philos)[i].table = table;
		i++;
	}
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

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philos;

	if ((argc != 5 && argc != 6) || !are_args_valid(argv))
	{
		write(2, "input error\n", 12);
		write(2, "./philo number_of_philosophers \
time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n", 113);
		return (1);
	}
	init_vars(&table, &philos, argc, argv);
	create_threads(philos, &table);
	return (0);
}
