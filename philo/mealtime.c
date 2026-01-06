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

/* Lock forks in an order that avoids deadlock. */
void	pick_up_forks(t_philo *philo)
{
	long	now;

	/* Last philosopher breaks the cycle to prevent deadlock */
	if (philo->id == philo->monitor->num_of_phil)
	{
		pthread_mutex_lock(&philo->right_fork_mutex);
		if (!philo->monitor->someone_died)
		{
			pthread_mutex_lock(&philo->monitor->print_mutex);
			now = get_current_time_ms();
			printf("%ld %d has taken a fork\n", now - philo->monitor->start_time_ms, philo->id);
			pthread_mutex_unlock(&philo->monitor->print_mutex);
		}
		pthread_mutex_lock(philo->left_fork_mutex);
		if (!philo->monitor->someone_died)
		{
			pthread_mutex_lock(&philo->monitor->print_mutex);
			now = get_current_time_ms();
			printf("%ld %d has taken a fork\n", now - philo->monitor->start_time_ms, philo->id);
			pthread_mutex_unlock(&philo->monitor->print_mutex);
		}
	}
	else
	{
		pthread_mutex_lock(philo->left_fork_mutex);
		if (!philo->monitor->someone_died)
		{
			pthread_mutex_lock(&philo->monitor->print_mutex);
			now = get_current_time_ms();
			printf("%ld %d has taken a fork\n", now - philo->monitor->start_time_ms, philo->id);
			pthread_mutex_unlock(&philo->monitor->print_mutex);
		}
		pthread_mutex_lock(&philo->right_fork_mutex);
		if (!philo->monitor->someone_died)
		{
			pthread_mutex_lock(&philo->monitor->print_mutex);
			now = get_current_time_ms();
			printf("%ld %d has taken a fork\n", now - philo->monitor->start_time_ms, philo->id);
			pthread_mutex_unlock(&philo->monitor->print_mutex);
		}
	}
}

/* Record eating state, update meal time/count, and sleep eating duration. */
void	eat(t_philo *philo)
{
	long	now;
	int		died;

	pthread_mutex_lock(&philo->monitor->death_mutex);
	died = philo->monitor->someone_died;
	pthread_mutex_unlock(&philo->monitor->death_mutex);
	if (died)
		return ;
	pthread_mutex_lock(&philo->monitor->print_mutex);
	now = get_current_time_ms();
	philo->last_meal_time_ms = now;
	philo->meals_eaten++;
	printf("%ld %d is eating\n", now - philo->monitor->start_time_ms, philo->id);
	pthread_mutex_unlock(&philo->monitor->print_mutex);
	custom_sleep(philo->time_to_eat);
}

/* Unlock both forks after eating. */
void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork_mutex);
	pthread_mutex_unlock(&philo->right_fork_mutex);
}

/* Lock forks in an order that avoids deadlock.
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

 Record eating state, update meal time/count, and sleep eating duration. 
void	eat(t_philo *philo)
{
	long	now;

	pthread_mutex_lock(&philo->monitor->print_mutex);
	now = get_current_time_ms();
	if (philo->monitor->someone_died)
	{
		pthread_mutex_unlock(&philo->monitor->print_mutex);
		return ;
	}
	printf("%ld %d has taken a fork\n", now - philo->monitor->start_time_ms, philo->id);
	printf("%ld %d has taken a fork\n", now - philo->monitor->start_time_ms, philo->id);
	printf("%ld %d is eating\n", now - philo->monitor->start_time_ms, philo->id);
	philo->meals_eaten++;
	philo->last_meal_time_ms = now;
	pthread_mutex_unlock(&philo->monitor->print_mutex);
	custom_sleep(philo->time_to_eat);
}

 Unlock both forks after eating. 
void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork_mutex);
	pthread_mutex_unlock(&philo->right_fork_mutex);
}*/

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
