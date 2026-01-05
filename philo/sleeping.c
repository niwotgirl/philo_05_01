/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:53:22 by aabelkis          #+#    #+#             */
/*   Updated: 2025/11/20 17:47:44 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Sleep for duration_ms using short usleep steps. */
void	custom_sleep(int duration_ms)
{
	long	start;

	start = get_current_time_ms();
	while (get_current_time_ms() - start < duration_ms)
		usleep(100); // sleep 100 µs steps
}
