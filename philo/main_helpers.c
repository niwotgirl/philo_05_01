/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:54:21 by aabelkis          #+#    #+#             */
/*   Updated: 2026/01/06 14:46:57 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Print usage message and return error. */
static int	usage_error(void)
{
	printf("error: invalid arguments\n");
	return (1);
}

/* Validate all arguments before any initialization. */
static int	validate_all_args(int argc, char **argv)
{
	int	i;
	int	val;

	if (argc < 5 || argc > 6)
		return (usage_error());
	i = 1;
	while (i < argc)
	{
		val = ft_error(argv, i);
		if (val < 0)
			return (1);
		i++;
	}
	return (0);
}

/* Validate args, allocate monitor, and init shared state. */
int	validate_and_init(int argc, char **argv, t_monitor *m)
{
	if (validate_all_args(argc, argv))
		return (1);
	m->num_of_phil = ft_error_atoi(argv[1]);
	m->philos = malloc(sizeof(t_philo) * m->num_of_phil);
	if (!m->philos)
		return (1);
	memset(m->philos, 0, sizeof(t_philo) * m->num_of_phil);
	m->someone_died = 0;
	m->start_time_ms = 0;
	pthread_mutex_init(&m->print_mutex, NULL);
	pthread_mutex_init(&m->death_mutex, NULL);
	return (0);
}

/* Populate each philosopher struct with parsed config. */
void	init_philosophers(int argc, char **argv, t_monitor *m)
{
	int	i;

	i = 0;
	while (i < m->num_of_phil)
	{
		struct_init(ft_error_atoi(argv[2]), i, 2, &m->philos[i]);
		struct_init(ft_error_atoi(argv[3]), i, 3, &m->philos[i]);
		struct_init(ft_error_atoi(argv[4]), i, 4, &m->philos[i]);
		if (argc == 6)
			struct_init(ft_error_atoi(argv[5]), i, 5, &m->philos[i]);
		m->philos[i].id = i + 1;
		m->philos[i].monitor = m;
		m->philos[i].last_meal_time_ms = 0;
		i++;
	}
}

/* Handle the single philosopher edge case: wait and report death. */
int	handle_single_philosopher(t_monitor *m)
{
	long		start;

	if (m->num_of_phil != 1)
		return (0);
	pthread_mutex_lock(&m->philos[0].right_fork_mutex);
	pthread_mutex_lock(&m->print_mutex);
	printf("0 1 has taken a fork\n");
	pthread_mutex_unlock(&m->print_mutex);
	start = get_current_time_ms();
	while (get_current_time_ms() - start < m->philos[0].time_to_die)
		usleep(1000);
	pthread_mutex_lock(&m->print_mutex);
	printf("%ld 1 died\n", get_current_time_ms() - m->start_time_ms);
	pthread_mutex_unlock(&m->print_mutex);
	pthread_mutex_unlock(&m->philos[0].right_fork_mutex);
	pthread_mutex_destroy(&m->philos[0].right_fork_mutex);
	pthread_mutex_destroy(&m->philos[0].meal_mutex);
	pthread_mutex_destroy(&m->print_mutex);
	pthread_mutex_destroy(&m->death_mutex);
	free(m->philos);
	return (1);
}
