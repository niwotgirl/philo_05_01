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

void	struct_init(int val, int j, int i, t_philo *philo) //j needed for ID, i so I know which arg, val so I know what the val is, and philo so I know where to store it
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
