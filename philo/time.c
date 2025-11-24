/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:21:46 by aabelkis          #+#    #+#             */
/*   Updated: 2025/11/20 17:53:47 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_current_time_ms(void)
{
	struct timeval	tval;

	gettimeofday(&tval, NULL);
	return (tval.tv_sec * 1000L + tval.tv_usec / 1000L);
}

long	longtimestamp_ms(long start_time_ms)
{
	long	now;
	long	delta;

	now = get_current_time_ms();
	delta = now - start_time_ms;
	if (delta < 0)
		return (0);
	else
		return (delta);
}
