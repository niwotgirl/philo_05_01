/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 14:01:06 by aabelkis          #+#    #+#             */
/*   Updated: 2026/01/05 19:22:16 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Initialize fork mutexes and link left/right fork references. */
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
		m->philos[i].left_fork_mutex
			= &m->philos[(i + m->num_of_phil - 1)
			% m->num_of_phil].right_fork_mutex;
		i++;
	}
}

/* Spawn one thread per philosopher running routine(). */
void	create_philo_threads(t_monitor *m)
{
	int	i;

	i = 0;
	while (i < m->num_of_phil)
	{
		if (pthread_create(&m->philos[i].thread, NULL,
				&routine, &m->philos[i]) != 0)
		{
			printf("Error: failed to create philosopher thread %d\n", i + 1);
			m->someone_died = 1;
		}
		i++;
	}
}

/* Join all philosopher threads and the monitor thread. */
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

/* Tear down mutexes and free allocated monitor memory. */
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

/* Program entry: setup, run simulation, and clean up. */
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
