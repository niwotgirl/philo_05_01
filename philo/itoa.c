/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:50:07 by aabelkis          #+#    #+#             */
/*   Updated: 2025/10/20 11:46:41 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	len_of_int(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*ft_pos(int n, char *result, int len)
{
	while (n > 0)
	{
		result[len - 1] = ('0' + (n % 10));
		n /= 10;
		len--;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = len_of_int(n);
	result = malloc (len + 1);
	if (!result)
		return (NULL);
	if (n == 0)
	{
		result[0] = '0';
		result[1] = '\0';
		return (result);
	}
	result[len] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		n = n * -1;
	}
	if (n > 0)
		ft_pos(n, result, len);
	return (result);
}
