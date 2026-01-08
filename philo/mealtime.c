/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mealtime.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:16:22 by aabelkis          #+#    #+#             */
/*   Updated: 2026/01/06 15:38:57 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Lock two forks in order, printing when each is taken.
   Return 1 on success, 0 if death detected. */
static int	lock_two_forks(t_philo *philo, pthread_mutex_t *first,
	pthread_mutex_t *second)
{
	pthread_mutex_lock(first);
	if (!safe_print(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(first);
		return (0);
	}
	pthread_mutex_lock(second);
	if (!safe_print(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
		return (0);
	}
	return (1);
}

/* Lock forks in an order that avoids deadlock.
   If a death is signaled after acquiring any fork, 
   release held forks and return. */
void	pick_up_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		lock_two_forks(philo, &philo->right_fork_mutex, philo->left_fork_mutex);
	else
		lock_two_forks(philo, philo->left_fork_mutex, &philo->right_fork_mutex);
}

/* Record eating state, update meal time/count, and sleep eating duration. */
	/* Update meal time immediately after print to prevent monitor race */
void	eat(t_philo *philo)
{
	long	now;

	now = safe_print(philo, "is eating");
	if (!now)
		return ;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time_ms = now;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	custom_sleep(philo->time_to_eat);
}

/* Unlock both forks after eating. */
void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork_mutex);
	pthread_mutex_unlock(&philo->right_fork_mutex);
}

/* Return 1 if philosopher reached the optional meal quota. */
int	has_finished_meals(t_philo *philo)
{
	int	finished;

	pthread_mutex_lock(&philo->meal_mutex);
	finished = (philo->minimum_meals > 0
			&& philo->meals_eaten >= philo->minimum_meals);
	pthread_mutex_unlock(&philo->meal_mutex);
	return (finished);
}
