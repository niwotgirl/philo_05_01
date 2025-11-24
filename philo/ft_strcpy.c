/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:21:56 by aabelkis          #+#    #+#             */
/*   Updated: 2025/11/20 18:01:03 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	if (!dest || !src)
		return (dest);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (n > 0)
	{
		*d = *s;
		s++;
		d++;
		n--;
	}
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	size_t	n;
	char	*ptr;

	n = ft_strlen(s) + 1;
	ptr = (char *)malloc(n);
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(ptr, s, n);
	return (ptr);
}
