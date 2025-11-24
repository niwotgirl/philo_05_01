/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:51:50 by aabelkis          #+#    #+#             */
/*   Updated: 2025/11/20 17:59:06 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_routine(t_philo *philo, t_monitor *monitor)
{
	long	timestamp;

	pthread_mutex_lock(&monitor->print_mutex);
	if (monitor->someone_died)
	{
		pthread_mutex_unlock(&monitor->print_mutex);
		return ;
	}
	if (philo->has_new_status)
	{
		timestamp = get_current_time_ms() - monitor->start_time_ms;
		if (philo->status == 1)
			printf("%ld %d is eating\n", timestamp, philo->id);
		else if (philo->status == 2)
			printf("%ld %d is sleeping\n", timestamp, philo->id);
		else if (philo->status == 3)
			printf("%ld %d is thinking\n", timestamp, philo->id);
		philo->has_new_status = 0;
	}
	pthread_mutex_unlock(&monitor->print_mutex);
}
