/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 14:02:14 by aabelkis          #+#    #+#             */
/*   Updated: 2026/01/06 15:42:17 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Check global death flag; instruct thread to stop if set. */
int	exit_on_death(t_philo *philo)
{
	int	died;

	pthread_mutex_lock(&philo->monitor->death_mutex);
	died = philo->monitor->someone_died;
	pthread_mutex_unlock(&philo->monitor->death_mutex);
	return (died);
}

/* Set status to sleeping and pause for sleep duration. */
void	philo_sleep(t_philo *philo)
{
	long	now;
	int	died;

	/* First check: bail early if death already signaled. */
	pthread_mutex_lock(&philo->monitor->death_mutex);
	died = philo->monitor->someone_died;
	pthread_mutex_unlock(&philo->monitor->death_mutex);
	if (died)
		return ;

	/* Print under death mutex -> print mutex to avoid racing with death flag. */
	pthread_mutex_lock(&philo->monitor->death_mutex);
	died = philo->monitor->someone_died;
	if (!died)
	{
		pthread_mutex_lock(&philo->monitor->print_mutex);
		now = get_current_time_ms();
		printf("%ld %d is sleeping\n", now - philo->monitor->start_time_ms, philo->id);
		pthread_mutex_unlock(&philo->monitor->print_mutex);
	}
	pthread_mutex_unlock(&philo->monitor->death_mutex);

	/* Second check: skip the sleep duration if death was signaled after print. */
	pthread_mutex_lock(&philo->monitor->death_mutex);
	died = philo->monitor->someone_died;
	pthread_mutex_unlock(&philo->monitor->death_mutex);
	if (!died)
	    custom_sleep(philo->time_to_sleep);
}

/* Mark thinking if there is time before starvation window closes. */
void	philo_think(t_philo *philo)
{
	long	now;
	int	died;


	/* Always announce thinking unless a death is already signaled. */
	pthread_mutex_lock(&philo->monitor->death_mutex);
	died = philo->monitor->someone_died;
	pthread_mutex_unlock(&philo->monitor->death_mutex);
	if (died)
		return ;
	pthread_mutex_lock(&philo->monitor->print_mutex);
	now = get_current_time_ms();
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

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (exit_on_death(philo))
			break ;
		pick_up_forks(philo);
		eat(philo);
		release_forks(philo);
		// If max meals reached, break after last eat, but still log sleep/thinking
		if (has_finished_meals(philo))
		{
			philo_sleep(philo);
			philo_think(philo);
			break;
		}
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
