/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:51:50 by aabelkis          #+#    #+#             */
/*   Updated: 2026/01/06 14:46:57 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Atomically check death flag and print status if alive.
   Returns timestamp if printed, 0 if death detected. */
long	safe_print(t_philo *philo, char *status)
{
	long	now;
	int		died;

	pthread_mutex_lock(&philo->monitor->death_mutex);
	died = philo->monitor->someone_died;
	if (!died)
	{
		pthread_mutex_lock(&philo->monitor->print_mutex);
		now = get_current_time_ms();
		printf("%ld %d %s\n", now - philo->monitor->start_time_ms,
			philo->id, status);
		pthread_mutex_unlock(&philo->monitor->print_mutex);
	}
	pthread_mutex_unlock(&philo->monitor->death_mutex);
	if (died)
		return (0);
	return (now);
}

/* Print elapsed time and philosopher id prefix. */
void	print_timestamped_id(t_monitor_vars *vars)
{
	printf("%ld %d ", vars->now - vars->monitor->start_time_ms, vars->p->id);
}

/* Detect starvation for current philosopher; mark death once. */
int	check_philo_death(t_monitor_vars *vars)
{
	if (vars->now - vars->last_meal >= vars->p->time_to_die)
	{
		pthread_mutex_lock(&vars->monitor->death_mutex);
		vars->monitor->someone_died = 1;
		pthread_mutex_unlock(&vars->monitor->death_mutex);
		pthread_mutex_lock(&vars->monitor->print_mutex);
		printf("%ld %d died\n",
			vars->now - vars->monitor->start_time_ms, vars->p->id);
		pthread_mutex_unlock(&vars->monitor->print_mutex);
		return (1);
	}
	return (0);
}
