/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 14:01:06 by aabelkis          #+#    #+#             */
/*   Updated: 2025/11/26 16:30:35 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	validate_and_init(int argc, char **argv, t_monitor *m)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [meals]\n", argv[0]);
		return (1);
	}
	m->num_of_phil = ft_error(argc, argv, 1);
	if (m->num_of_phil <= 0)
		return (1);
	m->philos = malloc(sizeof(t_philo) * m->num_of_phil);
	if (!m->philos)
		return (1);
	memset(m->philos, 0, sizeof(t_philo) * m->num_of_phil);
	m->someone_died = 0;
	m->start_time_ms = get_current_time_ms();
	pthread_mutex_init(&m->print_mutex, NULL);
	return (0);
}

void	init_philosophers(int argc, char **argv, t_monitor *m)
{
	int	i;

	i = 0;
	while (i < m->num_of_phil)
	{
		struct_init(ft_error(argc, argv, 2), i, 2, &m->philos[i]);
		struct_init(ft_error(argc, argv, 3), i, 3, &m->philos[i]);
		struct_init(ft_error(argc, argv, 4), i, 4, &m->philos[i]);
		if (argc == 6)
			struct_init(ft_error(argc, argv, 5), i, 5, &m->philos[i]);
		m->philos[i].id = i + 1;
		m->philos[i].monitor = m;
		m->philos[i].last_meal_time_ms = m->start_time_ms;
		i++;
	}
}

int	handle_single_philosopher(t_monitor *m)
{
	long		start;

	if (m->num_of_phil != 1)
		return (0);
	pthread_mutex_lock(&m->print_mutex);
	printf("0 1 has taken a fork\n");
	pthread_mutex_unlock(&m->print_mutex);
	start = get_current_time_ms();
	while (get_current_time_ms() - start < m->philos[0].time_to_die)
		usleep(1000);
	pthread_mutex_lock(&m->print_mutex);
	printf("%ld 1 died\n", get_current_time_ms() - m->start_time_ms);
	pthread_mutex_unlock(&m->print_mutex);
	pthread_mutex_destroy(&m->print_mutex);
	free(m->philos);
	return (1);
}

void	init_forks(t_monitor *m)
{
	int	i;

	i = 0;
	while (i < m->num_of_phil)
	{
		pthread_mutex_init(&m->philos[i].right_fork_mutex, NULL);
		i++;
	}
	i = 0;
	while (i < m->num_of_phil)
	{
		m->philos[i].left_fork_mutex = &m->philos[(i + m->num_of_phil - 1) % m->num_of_phil].right_fork_mutex;
		i++;
	}
}

void	create_philo_threads(t_monitor *m)
{
	int	i;

	i = 0;
	while (i < m->num_of_phil)
	{
		if (pthread_create(&m->philos[i].thread, NULL, &routine, &m->philos[i]) != 0)
		{
			printf("Error: failed to create philosopher thread %d\n", i + 1);
			m->someone_died = 1;
		}
		i++;
	}
}

void	join_all_threads(t_monitor *m)
{
	int	i;

	i = 0;
	while (i < m->num_of_phil)
	{
		pthread_join(m->philos[i].thread, NULL);
		i++;
	}
	pthread_join(m->thread, NULL);
}

void	cleanup(t_monitor *m)
{
	int	i;

	i = 0;
	while (i < m->num_of_phil)
	{
		pthread_mutex_destroy(&m->philos[i].right_fork_mutex);
		i++;
	}
	pthread_mutex_destroy(&m->print_mutex);
	free(m->philos);
}

int	main(int argc, char **argv)
{
	t_monitor	mon;

	if (validate_and_init(argc, argv, &mon))
		return (1);
	init_philosophers(argc, argv, &mon);
	if (handle_single_philosopher(&mon))
		return (0);
	init_forks(&mon);
	create_philo_threads(&mon);
	pthread_create(&mon.thread, NULL, &monitor_routine, &mon);
	join_all_threads(&mon);
	cleanup(&mon);
	return (0);
}
