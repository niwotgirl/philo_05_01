/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 14:02:14 by aabelkis          #+#    #+#             */
/*   Updated: 2026/01/05 20:44:59 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Check global death flag; instruct thread to stop if set. */
int	exit_on_death(t_philo *philo)
{
	int	died;

	pthread_mutex_lock(&philo->monitor->print_mutex);
	died = philo->monitor->someone_died;
	pthread_mutex_unlock(&philo->monitor->print_mutex);
	return (died);
}

/* Set status to sleeping and pause for sleep duration. */
void	philo_sleep(t_philo *philo)
{
	long	now;

	pthread_mutex_lock(&philo->monitor->print_mutex);
	now = get_current_time_ms();
	if (!philo->monitor->someone_died)
		printf("%ld %d is sleeping\n", now - philo->monitor->start_time_ms, philo->id);
	pthread_mutex_unlock(&philo->monitor->print_mutex);
	custom_sleep(philo->time_to_sleep);
}

/* Mark thinking if there is time before starvation window closes. */
void	philo_think(t_philo *philo)
{
	long	now;
	long	last_meal;

	pthread_mutex_lock(&philo->monitor->print_mutex);
	now = get_current_time_ms();
	last_meal = philo->last_meal_time_ms;
	if (now + 1 < last_meal + philo->time_to_die && !philo->monitor->someone_died)
		printf("%ld %d is thinking\n", now - philo->monitor->start_time_ms, philo->id);
	pthread_mutex_unlock(&philo->monitor->print_mutex);
}
/*unused version void	philo_think(t_philo *philo)
{
	long	now;
	long	last_meal;

	now = get_current_time_ms();
	pthread_mutex_lock(&philo->monitor->print_mutex);
	last_meal = philo->last_meal_time_ms;
	pthread_mutex_unlock(&philo->monitor->print_mutex);
	if (now + 1 < last_meal + philo->time_to_die)
	{
		pthread_mutex_lock(&philo->monitor->print_mutex);
		philo->status = 3; // thinking
		philo->has_new_status = 1;
		pthread_mutex_unlock(&philo->monitor->print_mutex);
	}
}*/

/* Philosopher thread loop: eat, sleep, think until done or death. */
void	*routine(void *arg)
{
	t_philo	*philo;
	int		has_meal_limit;

	philo = (t_philo *)arg;
	has_meal_limit = (philo->minimum_meals > 0); // understand this better
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (!has_meal_limit && exit_on_death(philo))
			break ; // idk if this is legal
		pick_up_forks(philo);
		eat(philo);
		release_forks(philo);
		if (has_finished_meals(philo))
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
