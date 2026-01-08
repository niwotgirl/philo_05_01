/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 14:02:35 by aabelkis          #+#    #+#             */
/*   Updated: 2025/11/20 17:57:55 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Write parsed argument value into the appropriate t_philo field. */
/*ID is base 1*/
void	struct_init(int val, int j, int i, t_philo *philo)
{
	if (i == 2)
	{
		philo->id = j + 1;
		philo->time_to_die = val;
	}
	else if (i == 3)
		philo->time_to_eat = val;
	else if (i == 4)
		philo->time_to_sleep = val;
	else if (i == 5)
		philo->minimum_meals = val;
}

/*init for monitor variables*/
/* Abort if someone died; otherwise prime monitor loop counters/timestamp. */
int	check_someone_died_and_init(t_monitor_vars *vars)
{
	int	someone_died;

	pthread_mutex_lock(&vars->monitor->death_mutex);
	someone_died = vars->monitor->someone_died;
	pthread_mutex_unlock(&vars->monitor->death_mutex);
	if (someone_died)
		return (1);
	vars->now = get_current_time_ms();
	vars->i = 0;
	vars->all_done = 1;
	return (0);
}
