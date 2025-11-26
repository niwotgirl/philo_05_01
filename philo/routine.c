/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 14:02:14 by aabelkis          #+#    #+#             */
/*   Updated: 2025/11/26 15:55:57 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	exit_on_death(t_philo *philo)
{
	int	died;

	pthread_mutex_lock(&philo->monitor->print_mutex);
	died = philo->monitor->someone_died;
	pthread_mutex_unlock(&philo->monitor->print_mutex);
	return (died);
}

void	pick_up_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->left_fork_mutex);
		pthread_mutex_lock(&philo->right_fork_mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork_mutex);
		pthread_mutex_lock(philo->left_fork_mutex);
	}
}

void	eat(t_philo *philo)
{
	long	now;

	now = get_current_time_ms();
	pthread_mutex_lock(&philo->monitor->print_mutex);
	philo->last_meal_time_ms = now;
	philo->status = 1; // eating
	philo->has_new_status = 1;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->monitor->print_mutex);
	custom_sleep(philo->time_to_eat);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork_mutex);
	pthread_mutex_unlock(&philo->right_fork_mutex);
}

int	has_finished_meals(t_philo *philo)
{
	int	finished;

	pthread_mutex_lock(&philo->monitor->print_mutex);
	finished = (philo->minimum_meals > 0
			&& philo->meals_eaten >= philo->minimum_meals);
	pthread_mutex_unlock(&philo->monitor->print_mutex);
	return (finished);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->monitor->print_mutex);
	philo->status = 2; // sleeping
	philo->has_new_status = 1;
	pthread_mutex_unlock(&philo->monitor->print_mutex);
	custom_sleep(philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	long	now;

	now = get_current_time_ms();
	if (now + 1 < philo->last_meal_time_ms + philo->time_to_die)
	{
		pthread_mutex_lock(&philo->monitor->print_mutex);
		philo->status = 3; // thinking
		philo->has_new_status = 1;
		pthread_mutex_unlock(&philo->monitor->print_mutex);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (exit_on_death(philo))
			break ;
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
