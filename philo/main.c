/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 14:01:06 by aabelkis          #+#    #+#             */
/*   Updated: 2025/11/24 15:35:58 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*int	main(int argc, char **argv)
{
	int			i;
	int			num_of_phil;
	t_philo		*philo_st;
	t_monitor	monitor;
	long		start;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (1);
	}
	num_of_phil = ft_error(argc, argv, 1);
	if (num_of_phil <= 0)
		return (1);
	philo_st = malloc(sizeof(t_philo) * num_of_phil);
	if (!philo_st)
		return (1);
	memset(philo_st, 0, sizeof(t_philo) * num_of_phil);
	monitor.philos = philo_st;
	monitor.num_of_phil = num_of_phil;
	monitor.someone_died = 0;
	monitor.start_time_ms = get_current_time_ms();
	pthread_mutex_init(&monitor.print_mutex, NULL);
	// Initialize philosophers
	i = 0;
	while (i < num_of_phil)
	{
		struct_init(ft_error(argc, argv, 2), i, 2, &philo_st[i]);
		struct_init(ft_error(argc, argv, 3), i, 3, &philo_st[i]);
		struct_init(ft_error(argc, argv, 4), i, 4, &philo_st[i]);
		if (argc == 6)
			struct_init(ft_error(argc, argv, 5), i, 5, &philo_st[i]);
		philo_st[i].id = i + 1;
		philo_st[i].monitor = &monitor;
		philo_st[i].last_meal_time_ms = monitor.start_time_ms;
		i++;
	}
	// Special-case: single philosopher
	if (num_of_phil == 1)
	{
		pthread_mutex_lock(&monitor.print_mutex);
		printf("0 1 has taken a fork\n");
		pthread_mutex_unlock(&monitor.print_mutex);
		start = get_current_time_ms();
		while (get_current_time_ms() - start < philo_st[0].time_to_die)
			usleep(1000);
		pthread_mutex_lock(&monitor.print_mutex);
		printf("%ld 1 died\n", get_current_time_ms() - monitor.start_time_ms);
		pthread_mutex_unlock(&monitor.print_mutex);
		pthread_mutex_destroy(&monitor.print_mutex);
		free(philo_st);
		return (0);
	}
	// Initialize right fork mutexes
	i = 0;
	while (i < num_of_phil)
	{
		pthread_mutex_init(&philo_st[i].right_fork_mutex, NULL);
		i++;
	}
	// Assign left fork pointers
	i = 0;
	while (i < num_of_phil)
	{
		philo_st[i].left_fork_mutex = &philo_st[(i + num_of_phil - 1) % num_of_phil].right_fork_mutex;
		i++;
	}
	// Create philosopher threads
	i = 0;
	while (i < num_of_phil)
	{
		if (pthread_create(&philo_st[i].thread, NULL, &routine, &philo_st[i]) != 0)
		{
			printf("Error: failed to create philosopher thread %d\n", i + 1);
			monitor.someone_died = 1;
		}
		i++;
	}
	// Start monitor thread
	pthread_create(&monitor.thread, NULL, &monitor_routine, &monitor);
	// Join philosopher threads
	i = 0;
	while (i < num_of_phil)
	{
		pthread_join(philo_st[i].thread, NULL);
		i++;
	}
	// Join monitor thread
	pthread_join(monitor.thread, NULL);
	// Destroy mutexes
	i = 0;
	while (i < num_of_phil)
	{
		pthread_mutex_destroy(&philo_st[i].right_fork_mutex);
		i++;
	}
	pthread_mutex_destroy(&monitor.print_mutex);
	free(philo_st);
	return (0);
}*/

int	validate_and_init(int argc, char **argv, t_main_vars *v)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [meals]\n", argv[0]);
		return (1);
	}
	v->num_of_phil = ft_error(argc, argv, 1);
	if (v->num_of_phil <= 0)
		return (1);
	v->philos = malloc(sizeof(t_philo) * v->num_of_phil);
	if (!v->philos)
		return (1);
	memset(v->philos, 0, sizeof(t_philo) * v->num_of_phil);
	v->monitor.philos = v->philos;
	v->monitor.num_of_phil = v->num_of_phil;
	v->monitor.someone_died = 0;
	v->monitor.start_time_ms = get_current_time_ms();
	pthread_mutex_init(&v->monitor.print_mutex, NULL);
	return (0);
}

void	init_philosophers(int argc, char **argv, t_main_vars *v)
{
	int	i;

	i = 0;
	while (i < v->num_of_phil)
	{
		struct_init(ft_error(argc, argv, 2), i, 2, &v->philos[i]);
		struct_init(ft_error(argc, argv, 3), i, 3, &v->philos[i]);
		struct_init(ft_error(argc, argv, 4), i, 4, &v->philos[i]);
		if (argc == 6)
			struct_init(ft_error(argc, argv, 5), i, 5, &v->philos[i]);
		v->philos[i].id = i + 1;
		v->philos[i].monitor = &v->monitor;
		v->philos[i].last_meal_time_ms = v->monitor.start_time_ms;
		i++;
	}
}

int	handle_single_philosopher(t_main_vars *v)
{
	t_monitor	*m; //whyy
	long		start;

	m = &v->monitor;
	if (v->num_of_phil != 1)
		return (0);
	pthread_mutex_lock(&m->print_mutex);
	printf("0 1 has taken a fork\n");
	pthread_mutex_unlock(&m->print_mutex);
	start = get_current_time_ms();
	while (get_current_time_ms() - start < v->philos[0].time_to_die)
		usleep(1000);
	pthread_mutex_lock(&m->print_mutex);
	printf("%ld 1 died\n", get_current_time_ms() - m->start_time_ms);
	pthread_mutex_unlock(&m->print_mutex);
	pthread_mutex_destroy(&m->print_mutex);
	free(v->philos);
	return (1);
}

void	init_forks(t_main_vars *v)
{
	int	i;

	i = 0;
	while (i < v->num_of_phil)
	{
		pthread_mutex_init(&v->philos[i].right_fork_mutex, NULL);
		i++;
	}
	i = 0;
	while (i < v->num_of_phil)
	{
		v->philos[i].left_fork_mutex = &v->philos[(i + v->num_of_phil - 1) % v->num_of_phil].right_fork_mutex;
		i++;
	}
}

void	create_philo_threads(t_main_vars *v)
{
	int	i;

	i = 0;
	while (i < v->num_of_phil)
	{
		if (pthread_create(&v->philos[i].thread, NULL, &routine, &v->philos[i]) != 0)
		{
			printf("Error: failed to create philosopher thread %d\n", i + 1);
			v->monitor.someone_died = 1;
		}
		i++;
	}
}

void	launch_monitor(t_main_vars *v)
{
	pthread_create(&v->monitor.thread, NULL, &monitor_routine, &v->monitor);
}

void	join_all_threads(t_main_vars *v)
{
	int	i;

	i = 0;
	while (i < v->num_of_phil)
	{
		pthread_join(v->philos[i].thread, NULL);
		i++;
	}
	pthread_join(v->monitor.thread, NULL);
}

void	cleanup(t_main_vars *v)
{
	int	i;

	i = 0;
	while (i < v->num_of_phil)
	{
		pthread_mutex_destroy(&v->philos[i].right_fork_mutex);
		i++;
	}
	pthread_mutex_destroy(&v->monitor.print_mutex);
	free(v->philos);
}

int	main(int argc, char **argv)
{
	t_main_vars	vars;

	if (validate_and_init(argc, argv, &vars))
		return (1);
	init_philosophers(argc, argv, &vars);
	if (handle_single_philosopher(&vars))
		return (0);
	init_forks(&vars);
	create_philo_threads(&vars);
	launch_monitor(&vars);
	join_all_threads(&vars);
	cleanup(&vars);
	return (0);
}
