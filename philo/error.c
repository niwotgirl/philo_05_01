/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:59:40 by aabelkis          #+#    #+#             */
/*   Updated: 2026/01/05 16:51:19 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*Your program(s) must take the following arguments:
[1]number_of_philosophers [2]time_to_die [3]time_to_eat [4]time_to_sleep
[5][number_of_times_each_philosopher_must_eat]*/
/* Validate a single numeric argument; returns parsed value or -1 on error. */
int	ft_error(char **argv, int i)
{
	int	val;

	val = ft_error_atoi(argv[i]);
	if (val < 0)
	{
		printf("error: invalid arguments - only positive numbers allowed\n");
		return (-1);
	}
	if (i == 1 && val == 0)
	{
		printf("error: invalid arguments - minimum 1 philosopher needed\n");
		return (-1);
	}
	return (val);
}
