/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:59:10 by aabelkis          #+#    #+#             */
/*   Updated: 2025/11/24 15:48:32 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*int	ft_error_atoi(const char *nptr)
{
	int		i;
	long	result;
	int		has_digit;

	i = 0;
	result = 0;
	has_digit = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '+')
		i++;
	if (nptr[i] == '-')
		return (-1);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		has_digit = 1;
		result = result * 10 + (nptr[i] - '0');
		if (result > INT_MAX)
			return (-1);
		i++;
	}
	if (!has_digit || nptr[i] != '\0')
		return (-1);
	return ((int)result);
}*/

int	skip_ws_and_check_sign(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '+')
		i++;
	if (nptr[i] == '-')
		return (-1);
	return (i);
}

int	ft_error_atoi(const char *nptr)
{
	int		i;
	long	result;
	int		has_digit;

	result = 0;
	has_digit = 0;
	i = skip_ws_and_check_sign(nptr);
	if (i == -1)
		return (-1);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		has_digit = 1;
		result = result * 10 + (nptr[i] - '0');
		if (result > INT_MAX)
			return (-1);
		i++;
	}
	if (!has_digit || nptr[i] != '\0')
		return (-1);
	return ((int)result);
}
