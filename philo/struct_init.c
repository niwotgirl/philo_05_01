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
void	struct_init(int val, int j, int i, t_philo *philo)
{
	if (i == 2)
	{
		philo->id = j + 1; // make id 1-based
		philo->time_to_die = val;
	}
	else if (i == 3)
		philo->time_to_eat = val;
	else if (i == 4)
		philo->time_to_sleep = val;
	else if (i == 5)
		philo->minimum_meals = val;
}
