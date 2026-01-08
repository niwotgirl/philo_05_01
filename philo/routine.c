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
	/* Check if death was signaled after print before sleeping */
void	philo_sleep(t_philo *philo)
{
	int	died;

	if (!safe_print(philo, "is sleeping"))
		return ;
	pthread_mutex_lock(&philo->monitor->death_mutex);
	died = philo->monitor->someone_died;
	pthread_mutex_unlock(&philo->monitor->death_mutex);
	if (!died)
		custom_sleep(philo->time_to_sleep);
}

/* Mark thinking if there is time before starvation window closes. */
	/* Small delay only for odd-count with very comfortable margins (>250ms) */
			/* Only add delay if we have >250ms margin after one full cycle */
void	philo_think(t_philo *philo)
{
	int		think_time;

	if (!safe_print(philo, "is thinking"))
		return ;
	if (philo->monitor->num_of_phil % 2 == 1
		&& philo->monitor->num_of_phil <= 7)
	{
		think_time = philo->time_to_die - philo->time_to_eat
			- philo->time_to_sleep;
		if (think_time > 250)
		{
			usleep((philo->time_to_eat / 4) * 1000);
		}
	}
}

/* Philosopher thread loop: eat, sleep, think until done or death. */
/* Stagger startup for better fairness:
	   - Large counts (≥100): odd IDs wait 1ms
	   - Medium counts (6-99) with even number: 
	   		odd IDs wait 500µs for fairness */
// If max meals reached, break after last eat, but still log sleep/thinking
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->monitor->num_of_phil >= 100 && philo->id % 2 == 1)
		usleep(1000);
	else if (philo->monitor->num_of_phil % 2 == 0
		&& philo->monitor->num_of_phil >= 6 && philo->id % 2 == 1)
		usleep(500);
	while (1)
	{
		if (exit_on_death(philo))
			break ;
		pick_up_forks(philo);
		eat(philo);
		release_forks(philo);
		if (has_finished_meals(philo))
		{
			philo_sleep(philo);
			philo_think(philo);
			break ;
		}
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
